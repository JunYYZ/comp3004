#include "mainWindow.h"
#include "ui_mainWindow.h"

#include "HomePage.h"
#include "LockPage.h"
#include "StatusPage.h"
#include "BolusPage.h"
#include "GraphPage.h"
#include "HistoryLogPage.h"
#include "ProfileListPage.h"
#include "PumpInfoPage.h"
#include "SettingsPage.h"
#include "ControlIQPage.h"

#include <QDebug>
#include <QTimer>
#include <QTime>      // for converting minutes→hh:mm:ss

mainWindow::mainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::mainWindow)
    // 1000 ms real interval, 5 simulated minutes per tick:
    , m_clock(new SimulationClock(1000, 5, this))
    , m_pump(new Pump(this))
    , m_profileManager(new ProfileManager(this))
    , pageHome(new HomePage(this))
    , pageLock(new LockPage(this))
    , pageStatus(new StatusPage(this))
    , pageBolus(new BolusPage(this))
    , pageGraph(new GraphPage(this))
    , pageHistoryLog(new HistoryLogPage(m_pump, this))
    , pageProfileList(new ProfileListPage(this))
    , pageProfileEditor(new ProfileEditorPage(m_profileManager, this))
    , pagePumpInfo(new PumpInfoPage(this))
    , pageSettings(new SettingsPage(this))
    , pageControlIQ(new ControlIQPage(this))
{
    ui->setupUi(this);

    // supply the clock to pages that need it:
    pageHistoryLog->setSimulationClock(m_clock);

    // menuHome is disabled until unlocked
    ui->menuHome->setEnabled(false);

    pageBolus->setProfileManager(m_profileManager);
    pageBolus->setPump(m_pump);
    pageProfileList->setProfileManager(m_profileManager);


    // wire up menu actions (QMenu::aboutToShow)
    connect(ui->menuHome, &QMenu::aboutToShow, this, &mainWindow::onActionHome);
    connect(ui->menuLock, &QMenu::aboutToShow, this, &mainWindow::onActionLock);
    connect(ui->menuCharge_Battery, &QMenu::aboutToShow,
                this,               &mainWindow::onChargeBattery);
    // build our stacked widget
    ui->stackedPages->addWidget(pageLock);
    ui->stackedPages->addWidget(pageHome);
    ui->stackedPages->addWidget(pageStatus);
    ui->stackedPages->addWidget(pageBolus);
    ui->stackedPages->addWidget(pageGraph);
    ui->stackedPages->addWidget(pageHistoryLog);
    ui->stackedPages->addWidget(pageProfileList);
    ui->stackedPages->addWidget(pageProfileEditor);
    ui->stackedPages->addWidget(pagePumpInfo);
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

    // show initial “00:00” battery/profile
    updateStatusBar(0);

    // whenever a profile changes, update our statusbar
    connect(m_profileManager, &ProfileManager::profileChanged,
        this,                &mainWindow::refreshStatusBar,
        Qt::QueuedConnection);

}

mainWindow::~mainWindow()
{
    delete ui;
}

void mainWindow::connectPageSignals()
{
    // --- HomePage navigation buttons ---
    connect(pageHome, &HomePage::gotoStatus,     this, &mainWindow::onActionStatus);
    connect(pageHome, &HomePage::gotoBolus,      this, &mainWindow::onActionBolus);
    connect(pageHome, &HomePage::gotoGraph,      this, &mainWindow::onActionGraph);
    connect(pageHome, &HomePage::gotoHistory,    this, &mainWindow::onActionHistoryLog);
    connect(pageHome, &HomePage::gotoInsulin,    this, &mainWindow::onActionInsulin);
    connect(pageHome, &HomePage::loadCartridge,  this, &mainWindow::onLoadCartridge);
    connect(pageHome, &HomePage::gotoProfiles,   this, &mainWindow::onActionProfileList);
    connect(pageHome, &HomePage::gotoPumpInfo,   this, &mainWindow::onActionPumpInfo);
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

    // --- StatusPage back ---
    connect(pageStatus, &StatusPage::backRequested,
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

void mainWindow::onActionStatus()
{ ui->stackedPages->setCurrentWidget(pageStatus); }

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

void mainWindow::onActionPumpInfo()
{ ui->stackedPages->setCurrentWidget(pagePumpInfo); }

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
}

void mainWindow::onActivateProfile(const QString &name)
{
    if (!m_profileManager->selectProfile(name)) {
        qWarning() << "Failed to activate profile" << name;
    }
}

void mainWindow::onEditProfile(const QString &name)
{
    Profile p = m_profileManager->getProfileByName(name);
    pageProfileEditor->setProfile(p);
    ui->stackedPages->setCurrentWidget(pageProfileEditor);
}

void mainWindow::onDeleteProfile(const QString &name)
{
    m_profileManager->removeProfile(name);
}

void mainWindow::onEditorAddProfile(const Profile& p)
{
    m_profileManager->addProfile(p);
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
    QString prof = m_profileManager->activeProfile().name();
    if (prof.isEmpty()) prof = QLatin1String("<none>");

    ui->statusbar->showMessage(
        QString("Time: %1    Battery: %2%    Profile: %3")
        .arg(t.toString("hh:mm:ss"))
        .arg(battery)
        .arg(prof)
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
