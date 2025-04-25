#include "mainWindow.h"
#include "ui_mainWindow.h"

#include "HomePage.h"
#include "LockPage.h"
#include "BolusPage.h"
#include "GraphPage.h"
#include "HistoryLogPage.h"
#include "ProfileListPage.h"
#include "SettingsPage.h"
#include "ControlIQPage.h"
#include "WarningDialog.h"
#include "HistoryLog.h"

#include <QMessageBox>
#include "ControlIQ.h"


#include <QDebug>
#include <QTimer>
#include <QTime>      // for converting minutes→hh:mm:ss
#include <QtGlobal>

mainWindow::mainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::mainWindow)
    // 1000 ms real interval, 5 simulated minutes per tick:
    , m_clock(new SimulationClock(1000, 5, this))
    , m_simTime(QDateTime::currentDateTime())
    , m_pump(new Pump(this))
    , m_profileManager(new ProfileManager(this))
    , pageHome(new HomePage(this))
    , pageLock(new LockPage(this))
    , pageBolus(new BolusPage(this))
    , pageGraph(new GraphPage(this))
    , pageHistoryLog(new HistoryLogPage(m_pump, this))
    , pageProfileList(new ProfileListPage(this))
    , pageProfileEditor(new ProfileEditorPage(m_profileManager, this))
    , pageSettings(new SettingsPage(this))
    , pageControlIQ(new ControlIQPage(this))
    , m_bgSim(new BGSimulator(this))

{
    m_ctrlIQ = new ControlIQ(m_pump, this);
    m_profileManager->loadProfilesFromFile();
    ui->setupUi(this);

    // supply the clock to pages that need it:
    pageHistoryLog->setSimulationClock(m_clock);


    pageBolus->setPump(m_pump);


    // menuHome is disabled until unlocked
    ui->menuHome->setEnabled(false);

    pageBolus->setProfileManager(m_profileManager);
    pageBolus->setPump(m_pump);
    pageProfileList->setProfileManager(m_profileManager);

    // Sync profiles into Pump:
    for (const Profile& p : m_profileManager->profiles()) {
        m_pump->addProfile(p);
    }
    m_pump->selectActiveProfile(m_profileManager->activeProfile().name());


    // wire up menu actions (QMenu::aboutToShow)
    connect(ui->menuHome, &QMenu::aboutToShow, this, &mainWindow::onActionHome);
    connect(ui->menuLock, &QMenu::aboutToShow, this, &mainWindow::onActionLock);
    connect(ui->menuCharge_Battery, &QMenu::aboutToShow,
                this,               &mainWindow::onChargeBattery);

    // pump status bar updates
    connect(m_pump, &Pump::insulinLevelChanged,
            this,   &mainWindow::refreshStatusBar);


    // build our stacked widget
    ui->stackedPages->addWidget(pageLock);
    ui->stackedPages->addWidget(pageHome);
    ui->stackedPages->addWidget(pageBolus);
    ui->stackedPages->addWidget(pageGraph);
    ui->stackedPages->addWidget(pageHistoryLog);
    ui->stackedPages->addWidget(pageProfileList);
    ui->stackedPages->addWidget(pageProfileEditor);
    ui->stackedPages->addWidget(pageSettings);
    ui->stackedPages->addWidget(pageControlIQ);

    // Start locked
    ui->stackedPages->setCurrentWidget(pageLock);

    // wire all the navigation signals
    connectPageSignals();
    connect(m_clock, &SimulationClock::tick,
            this,    &mainWindow::refreshStatusBar);
    connect(m_clock, &SimulationClock::tick,
            m_pump,   &Pump::onSimulatedTimeAdvanced);

    m_clock->start();
    // Connect BG simulator to profile
    m_bgSim->setProfile(m_profileManager->activeProfile());
    m_pump->selectActiveProfile(m_profileManager->activeProfile().name());
    pageControlIQ->setStatus( m_ctrlIQ->isEnabled() ? "Active" : "Off" );
    pageControlIQ->setCurrentBasal(
        m_profileManager->activeProfile().basalRate()
    );
    // Update BG simulator if profile changes
    connect(m_profileManager, &ProfileManager::profileChanged, this, [=]() {
        m_bgSim->setProfile(m_profileManager->activeProfile());
        m_pump->selectActiveProfile(m_profileManager->activeProfile().name());
    });
    // ── wire BGSimulator → Control-IQ ──
    connect(m_bgSim, &BGSimulator::newReading,
            m_ctrlIQ, &ControlIQ::onNewReading);

    // Connect simulation clock to BG updates
    connect(m_clock, &SimulationClock::tick,
            m_bgSim, &BGSimulator::onTick);

    // Connect bolus signal to BG simulator
    connect(m_pump, QOverload<double, int>::of(&Pump::bolusDelivered),
            m_bgSim, &BGSimulator::onBolusDelivered);

    // wire pump basal-rate signals to the UI
    connect(m_pump, &Pump::basalRateChanged,
            pageControlIQ, &ControlIQPage::setCurrentBasal);

    // Emit new glucose reading to graph
    connect(m_bgSim, &BGSimulator::newReading, this, [=](double bg) {
        static int timeStep = 0;
        pageGraph->addBGPoint(timeStep++, bg);
    });

    // Inside mainWindow.cpp
    connect(m_bgSim, &BGSimulator::newReading, pageBolus, &BolusPage::updateCurrentBG);


    // show initial “00:00” battery/profile
    updateStatusBar(0);

    // whenever a profile changes, update our statusbar
    connect(m_profileManager, &ProfileManager::profileChanged,
        this,                &mainWindow::refreshStatusBar,
        Qt::QueuedConnection);

    connect(m_pump, &Pump::warningRaised,
            this,   &mainWindow::onPumpWarning);

    connect(this, &mainWindow::guiLog,
            pageHistoryLog, &HistoryLogPage::addEntry);

    // Show a message when insulin on board (IOB) is depleted
    connect(m_pump, &Pump::iobChanged, this, [this](double u){
        if (u <= 0.0) {
            QMessageBox::information(
                this,
                tr("IOB Depleted"),
                tr("You have no active insulin on board.")
            );
        }
    });

    // Control IQ logic from dev-michael

    // Wire the "Turn On" button for Control-IQ
    connect(pageControlIQ, &ControlIQPage::controlIQTurnedOn, this, [this]() {
        m_ctrlIQ->setEnabled(true);  // Turn ControlIQ on
        pageControlIQ->setStatus("Active");
    });

    // Wire the "Turn Off" button for Control-IQ
    connect(pageControlIQ, &ControlIQPage::controlIQTurnedOff, this, [this]() {
        m_ctrlIQ->setEnabled(false);  // Turn ControlIQ off
        pageControlIQ->setStatus("Inactive");
    });

    // Update ControlIQ status based on its enabled state
    connect(m_ctrlIQ, &ControlIQ::enabledChanged, this, [=](bool on){
        pageControlIQ->setStatus(on ? "Active" : "Off");
    });

    // Update the predicted BG value in ControlIQPage
    connect(m_ctrlIQ, &ControlIQ::predictionMade, this, [=](double pred){
        if (qIsNaN(pred))
            pageControlIQ->setPredictedBG(0.0);  // Show 0.0 for NaN predictions
        else
            pageControlIQ->setPredictedBG(pred);  // Show the predicted BG
    });

    // Keep the "Current Basal" in sync with the pump's basal rate
    connect(m_pump, &Pump::basalRateChanged, this, [&](double rate) {
        pageControlIQ->setCurrentBasal(rate);  // Update current basal rate in UI
    });

}

mainWindow::~mainWindow()
{
    m_profileManager->saveProfilesToFile();
    delete ui;
}

void mainWindow::connectPageSignals()
{
    // --- HomePage navigation buttons ---
    connect(pageHome, &HomePage::gotoBolus,      this, &mainWindow::onActionBolus);
    connect(pageHome, &HomePage::gotoGraph,      this, &mainWindow::onActionGraph);
    connect(pageHome, &HomePage::gotoHistory,    this, &mainWindow::onActionHistoryLog);
    connect(pageHome, &HomePage::gotoInsulin,    this, &mainWindow::onActionInsulin);
    connect(pageHome, &HomePage::loadCartridge,  this, &mainWindow::onLoadCartridge);
    connect(pageHome, &HomePage::gotoProfiles,   this, &mainWindow::onActionProfileList);
    connect(pageHome, &HomePage::gotoSettings,   this, &mainWindow::onActionSettings);
    connect(pageHome, &HomePage::gotoControlIQ,  this, &mainWindow::onActionControlIQ);

    // --- LockPage unlock ---
    connect(pageLock, &LockPage::authenticated,  this, &mainWindow::onActionHome);

    // --- HistoryLogPage back ---
    connect(pageHistoryLog, &HistoryLogPage::backRequested,
            this, &mainWindow::onActionHome);

    // --- ProfileListPage ---
    connect(pageProfileList, &ProfileListPage::requestAddProfile,
            this,             &mainWindow::onAddProfile);
    connect(pageProfileList, &ProfileListPage::requestEditProfile,
            this,             &mainWindow::onEditProfile);
    connect(pageProfileList, &ProfileListPage::requestDeleteProfile,
            this,             &mainWindow::onDeleteProfile);
    connect(pageProfileList, &ProfileListPage::requestActivateProfile,
            this,             &mainWindow::onActivateProfile);
    connect(pageProfileList, &ProfileListPage::backRequested,
            this,             &mainWindow::onActionHome);

    // --- ProfileEditor ---
    connect(pageProfileEditor, &ProfileEditorPage::addProfile,
            this,                &mainWindow::onEditorAddProfile);
    connect(pageProfileEditor, &ProfileEditorPage::updateProfile,
            this,                &mainWindow::onEditorUpdateProfile);
    connect(pageProfileEditor, &ProfileEditorPage::cancel,
            this,                &mainWindow::onEditorCancel);

    // --- ControlIQ & Settings back ---
    connect(pageControlIQ, &ControlIQPage::backClicked,
            this,              &mainWindow::onActionHome);
    connect(pageSettings, &SettingsPage::backRequested,
            this,               &mainWindow::onActionHome);

    connect(pageBolus, &BolusPage::backClicked,
            this,               &mainWindow::onActionHome);

    connect(pageGraph, &GraphPage::backRequested,
            this,               &mainWindow::onActionHome);
}

// ----------------------------------------------------------------
// Navigation slots
// ----------------------------------------------------------------

void mainWindow::onActionHome()
{
    qDebug() << "Home clicked!";
    pageLock->reset();           // ensure lock screen is fresh
    ui->menuHome->setEnabled(true);
    ui->stackedPages->setCurrentWidget(pageHome);
}

void mainWindow::onActionLock()
{
    qDebug() << "Lock menu clicked!";
    pageLock->reset();
    ui->menuHome->setEnabled(false);
    ui->stackedPages->setCurrentWidget(pageLock);
}


void mainWindow::onActionBolus()
{ ui->stackedPages->setCurrentWidget(pageBolus); }

void mainWindow::onActionGraph()
{ ui->stackedPages->setCurrentWidget(pageGraph); }

void mainWindow::onActionHistoryLog()
{ ui->stackedPages->setCurrentWidget(pageHistoryLog); }

void mainWindow::onActionInsulin()
{
    // reuse BolusPage or whatever is appropriate
    ui->stackedPages->setCurrentWidget(pageBolus);
}

void mainWindow::onLoadCartridge()
{ ui->stackedPages->setCurrentWidget(pageSettings); }

void mainWindow::onActionProfileList()
{ ui->stackedPages->setCurrentWidget(pageProfileList); }

void mainWindow::onActionSettings()
{ ui->stackedPages->setCurrentWidget(pageSettings); }

void mainWindow::onActionControlIQ()
{ ui->stackedPages->setCurrentWidget(pageControlIQ); }

// ----------------------------------------------------------------
// Profile CRUD
// ----------------------------------------------------------------

void mainWindow::onAddProfile()
{
    pageProfileEditor->clearFields();
    ui->stackedPages->setCurrentWidget(pageProfileEditor);
    logEvent("added profile");
}

void mainWindow::onActivateProfile(const QString &name)
{
    if (!m_profileManager->selectProfile(name)) {
        qWarning() << "Failed to activate profile" << name;
        return;
    }
    m_pump->selectActiveProfile(name);

    logEvent("activated profile");

}

void mainWindow::onEditProfile(const QString &name)
{
    Profile p = m_profileManager->getProfileByName(name);
    pageProfileEditor->setProfile(p);
    ui->stackedPages->setCurrentWidget(pageProfileEditor);
    logEvent("edited profile");
}

void mainWindow::onDeleteProfile(const QString &name)
{
    m_profileManager->removeProfile(name);
    logEvent("deleted profile");
}

void mainWindow::onEditorAddProfile(const Profile& p)
{
    m_profileManager->addProfile(p);

    // Sync into Pump too:
    m_pump->addProfile(p);
    m_pump->selectActiveProfile(p.name());

    // Switch back to the list view
    ui->stackedPages->setCurrentWidget(pageProfileList);
}

void mainWindow::onEditorUpdateProfile(const QString& orig, const Profile& p)
{
    m_profileManager->updateProfile(orig, p);
    ui->stackedPages->setCurrentWidget(pageProfileList);
}

void mainWindow::onEditorCancel()
{
    ui->stackedPages->setCurrentWidget(pageProfileList);
}

// ----------------------------------------------------------------
// Status bar updater now takes simulated minutes
// ----------------------------------------------------------------

void mainWindow::updateStatusBar(int simMinutes)
{
    // convert minutes→ hh:mm:ss
    QTime t(0, 0);
    t = t.addSecs(simMinutes * 60);

    int battery = m_pump->batteryLevel();
    double basal = m_profileManager->activeProfile().basalRate();
    double insulin = m_pump->insulinLevel();
    QString prof = m_profileManager->activeProfile().name();
    if (prof.isEmpty()) prof = QLatin1String("<none>");

    ui->statusbar->showMessage(
        QString("Time %1   Profile %2   Basal %3 U/h   Insulin %4 U   Battery %5%")
        .arg(t.toString("hh:mm:ss"))
        .arg(prof)
        .arg(basal)
        .arg(insulin)
        .arg(battery)
    );
}

void mainWindow::refreshStatusBar() {
    updateStatusBar(m_clock->elapsedMinutes());
}

void mainWindow::onChargeBattery()
{
    m_pump->chargeBattery();
    // immediately refresh the status bar (time/batt/profile):
    updateStatusBar(m_clock->elapsedMinutes());
}

void mainWindow::onPumpWarning(ErrorHandler::Warning w, const QString &msg)
{
    // The dialog deletes itself on close because of Qt::WA_DeleteOnClose
    auto *dlg = new WarningDialog(w, msg, m_pump, this);
    dlg->setAttribute(Qt::WA_DeleteOnClose);
    dlg->show();
}

void mainWindow::logEvent(const QString &desc)
{
    m_history.append( HistoryLog(m_simTime, desc) );   // keep your own copy
    emit guiLog(desc);                                 // forward to the page
}

