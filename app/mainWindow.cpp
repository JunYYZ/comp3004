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

#include <QTimer>
#include <QDateTime>

mainWindow::mainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::mainWindow)
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

    ui->pageBolus->setProfileManager( m_profileManager );
    pageProfileList->setProfileManager(m_profileManager);

    // Add each page widget into the QstackedPages in the same order:
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

    // Hook up all the signals/slots for navigation
    connectPageSignals();

    // Kick off a timer for clock + battery indicator
    QTimer *t = new QTimer(this);
    connect(t, &QTimer::timeout, this, &mainWindow::updateStatusBar);
    t->start(1000);
    updateStatusBar();
}

mainWindow::~mainWindow()
{
    delete ui;  // pages are children and will delete themselves
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

    // --- LockPage unlock (via NumberKeypad inside LockPage) ---
    connect(pageLock, &LockPage::authenticated,  this, &mainWindow::onActionHome);

    // --- HistoryLogPage go back ----
    connect(pageHistoryLog, &HistoryLogPage::backRequested,
            this, &mainWindow::onActionHome);

    // ---  ProfileListPage ---
    connect(pageProfileList, &ProfileListPage::requestAddProfile,
            this,             &mainWindow::onAddProfile);
    connect(pageProfileList, &ProfileListPage::requestEditProfile,
            this,             &mainWindow::onEditProfile);
    connect(pageProfileList, &ProfileListPage::requestDeleteProfile,
            this,             &mainWindow::onDeleteProfile);
    connect(pageProfileList, &ProfileListPage::backRequested,
                this,               &mainWindow::onActionHome);
    // --- ProfileEditor Page ---
    connect(pageProfileEditor, &ProfileEditorPage::addProfile,
                this,                &mainWindow::onEditorAddProfile);
    connect(pageProfileEditor, &ProfileEditorPage::updateProfile,
                this,                &mainWindow::onEditorUpdateProfile);
    connect(pageProfileEditor, &ProfileEditorPage::cancel,
                this,                &mainWindow::onActionProfileList);

    connect(pageControlIQ, &ControlIQPage::backClicked,
             this,              &mainWindow::onActionHome);
}

void mainWindow::onActionHome()
{
    ui->stackedPages->setCurrentWidget(pageHome);
}

void mainWindow::onActionStatus()
{
    ui->stackedPages->setCurrentWidget(pageStatus);
}

void mainWindow::onActionBolus()
{
    ui->stackedPages->setCurrentWidget(pageBolus);
}

void mainWindow::onActionGraph()
{
    ui->stackedPages->setCurrentWidget(pageGraph);
}

void mainWindow::onActionHistoryLog()
{
    ui->stackedPages->setCurrentWidget(pageHistoryLog);
}

void mainWindow::onActionInsulin()
{
    // if you have a dedicated Insulin page:
    // ui->stackedPages->setCurrentWidget(pageInsulin);
    // otherwise reuse Bolus or Settings as appropriate
}

void mainWindow::onLoadCartridge()
{
    // maybe show a dialog, or:
    ui->stackedPages->setCurrentWidget(pageSettings);
}

void mainWindow::onActionProfileList()
{
    ui->stackedPages->setCurrentWidget(pageProfileList);
}

void mainWindow::onActionPumpInfo()
{
    ui->stackedPages->setCurrentWidget(pagePumpInfo);
}

void mainWindow::onActionSettings()
{
    ui->stackedPages->setCurrentWidget(pageSettings);
}

void mainWindow::onActionControlIQ()
{
    ui->stackedPages->setCurrentWidget(pageControlIQ);
}

void mainWindow::updateStatusBar()
{
    // current time
    QString t = QDateTime::currentDateTime().toString("hh:mm:ss");
    // dummy battery -- replace with your Pump::batteryLevel()
    int battery = 85;
    ui->statusbar->showMessage(
        QString("Time: %1    Battery: %2%").arg(t).arg(battery)
    );
}

void mainWindow::onAddProfile()
{
    // clear out whatever your editor page is showing...
    pageProfileEditor->clearFields();
    ui->stackedPages->setCurrentWidget(pageProfileEditor);
}

void mainWindow::onEditProfile(const QString &name)
{
    // lookup via our new helper
    Profile p = m_profileManager->getProfileByName(name);
    // pre‑load fields and switch to Edit mode
    pageProfileEditor->setProfile(p);
    ui->stackedPages->setCurrentWidget(pageProfileEditor);
}

void mainWindow::onDeleteProfile(const QString &name)
{
    m_profileManager->removeProfile(name);
    // the profileChanged() signal will fire and refresh the list automatically
}

void mainWindow::onEditorAddProfile(const Profile& p)
{
    // add it to the manager
    m_profileManager->addProfile(p);
    // then go back to the list page so they can see it
    ui->stackedPages->setCurrentWidget(pageProfileList);
}

void mainWindow::onEditorUpdateProfile(const QString& originalName,
                                       const Profile& p)
{
    // update in the manager
    m_profileManager->updateProfile(originalName, p);
    // back to list
    ui->stackedPages->setCurrentWidget(pageProfileList);
}

void mainWindow::onEditorCancel()
{
    // just go back to the list
    ui->stackedPages->setCurrentWidget(pageProfileList);
}

