#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "insulindeliverymanager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Slots for button actions.
    void onStartClicked();
    void onStopClicked();
    void onResumeClicked();

    // Slots to update the UI based on signals from InsulinDeliveryManager.
    void updateLog(const QString &msg);
    void onDeliveryStarted();
    void onDeliveryStopped();
    void onDeliveryResumed();
    void onErrorOccurred(const QString &errorMsg);

private:
    Ui::MainWindow *ui;
    InsulinDeliveryManager *deliveryManager;
};

#endif // MAINWINDOW_H

