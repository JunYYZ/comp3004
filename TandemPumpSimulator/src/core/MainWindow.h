#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

/* -------- Qt widgets we use -------- */
#include <QLabel>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QListWidget>
#include <QPushButton>

#include "InsulinPump.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    /* GUI buttons -------------------------------------------------------- */
    void onStartClicked();
    void onPauseClicked();
    void onResumeClicked();
    void onStopClicked();

    void onAddProfileClicked();
    void onSelectProfileClicked();

    void onBolusClicked();

    /* receive text logs from the pump */
    void handlePumpLog(const QString &msg);

    /* simulation‑time tick – called each real‑second                    */
    void onTimerTick();

private:
    void buildUI();
    void refresh(); // update labels with latest pump data

    /* --------------- widgets ------------------------------------------ */
    QLabel *m_lblBattery{nullptr};
    QLabel *m_lblInsulin{nullptr};
    QLabel *m_lblState{nullptr};
    QLabel *m_lblBG{nullptr};
    QLabel *lblSimTime;

    QPlainTextEdit *m_txtLog{nullptr};
    QListWidget *m_listProfiles{nullptr};

    QLineEdit *m_editBG{nullptr};
    QLineEdit *m_editCarb{nullptr};

    QPushButton *m_btnStart{nullptr};
    QPushButton *m_btnPause{nullptr};
    QPushButton *m_btnResume{nullptr};
    QPushButton *m_btnStop{nullptr};

    QTimer *m_timer{nullptr};

    /* --------------- simulation state --------------------------------- */
    bool m_running{false};
    int m_simTime{0};

    InsulinPump *m_pump; // created in ctor – lifetime == MainWindow
};

#endif // MAINWINDOW_H
