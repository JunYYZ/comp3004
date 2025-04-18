#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

    // status bar updates
    void updateStatusBar();

private:
    void connectPageSignals();

    Ui::mainWindow   *ui;

    // one member per page
    HomePage        *pageHome;
    LockPage        *pageLock;
    StatusPage      *pageStatus;
    BolusPage       *pageBolus;
    GraphPage       *pageGraph;
    HistoryLogPage  *pageHistoryLog;
    ProfileListPage *pageProfileList;
    PumpInfoPage    *pagePumpInfo;
    SettingsPage    *pageSettings;
    ControlIQPage   *pageControlIQ;
};

#endif // MAINWINDOW_H
