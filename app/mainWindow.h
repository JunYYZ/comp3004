#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Pump.h"
#include "ProfileManager.h"
#include "HistoryLogPage.h"
#include "ProfileEditorPage.h"
#include "SimulationClock.h"

class HomePage;
class LockPage;
class StatusPage;
class BolusPage;
class GraphPage;
class HistoryLogPage;
class ProfileListPage;
class PumpInfoPage;
class SettingsPage;
class ControlIQPage;

namespace Ui {
class mainWindow;
}

class mainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit mainWindow(QWidget *parent = nullptr);
    ~mainWindow();
    Pump* pump() const { return m_pump; }
    ProfileManager* profileManager() const { return m_profileManager;}

signals:
    void guiLog(const QString &msg);

private slots:
    // navigation
    void onActionHome();
    void onActionStatus();
    void onActionBolus();
    void onActionGraph();
    void onActionHistoryLog();
    void onActionInsulin();       // if you have a separate “insulin” page
    void onLoadCartridge();       // home→load‑cartridge shortcut
    void onActionProfileList();
    void onActionPumpInfo();
    void onActionSettings();
    void onActionControlIQ();
    void onActionLock();

    //profile-list actions
    void onAddProfile();
    void onActivateProfile(const QString &name);
    void onEditProfile(const QString &name);
    void onDeleteProfile(const QString &name);
    void onEditorAddProfile(const Profile& p);
    void onEditorUpdateProfile(const QString& originalName, const Profile& p);
    void onEditorCancel();

    // status bar updates
    void updateStatusBar(int simMinutes);
    void refreshStatusBar();
    void onChargeBattery();

    void onPumpWarning(ErrorHandler::Warning w, const QString& msg);
    void logEvent(const QString &desc);

private:
    void connectPageSignals();

    QVector<HistoryLog> m_history;    ///< Chronological event history
    Ui::mainWindow   *ui;

    // one member per page
    SimulationClock*  m_clock;
<<<<<<< HEAD
    Pump*             m_pump;
    CGM*              m_cgm;         // remove
    HistoryLogPage*   m_historypage;
    ProfileManager*   m_profileManager;
    HomePage*         pageHome;
    LockPage*         pageLock;
    StatusPage*       pageStatus;
    BolusPage*        pageBolus;
    GraphPage*        pageGraph;
    HistoryLogPage*   pageHistoryLog;
    ProfileListPage*  pageProfileList;
    ProfileEditorPage* pageProfileEditor;
    PumpInfoPage*     pagePumpInfo;
    SettingsPage*     pageSettings;
    ControlIQPage*    pageControlIQ;
    BGSimulator*      m_bgSim;
    QDateTime m_simTime;

=======
    Pump            *m_pump;
    HistoryLogPage* m_historypage;
    ProfileManager  *m_profileManager;
    HomePage        *pageHome;
    LockPage        *pageLock;
    StatusPage      *pageStatus;
    BolusPage       *pageBolus;
    GraphPage       *pageGraph;
    HistoryLogPage  *pageHistoryLog;
    ProfileListPage *pageProfileList;
    ProfileEditorPage *pageProfileEditor;
    PumpInfoPage    *pagePumpInfo;
    SettingsPage    *pageSettings;
    ControlIQPage   *pageControlIQ;
>>>>>>> parent of e5ef163 (Save work before push)
};

#endif // MAINWINDOW_H
