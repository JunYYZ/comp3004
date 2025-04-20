#include "insulindeliverymanagermodule.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Create an instance of InsulinDeliveryManager.
    deliveryManager = new InsulinDeliveryManager(this);

    // For demonstration, set an active profile.
    deliveryManager->setActiveProfile("DemoProfile", 1.2);  // 1.2 U/hr

    // Update the static labels.

    ui->labelActiveProfile->setText("Active Profile: " + QString("DemoProfile"));
    ui->labelBasalRate->setText("Basal Rate: " + QString("1.2 U/hr"));
    ui->labelInsulinRemaining->setText("Insulin Remaining: " + QString("300 U"));
    ui->labelStatus->setText("Status: " + QString("Stopped"));


    // Connect GUI buttons to their respective slots.
    connect(ui->pushButtonStart, &QPushButton::clicked, this, &MainWindow::onStartClicked);
    connect(ui->pushButtonStop, &QPushButton::clicked, this, &MainWindow::onStopClicked);
    connect(ui->pushButtonResume, &QPushButton::clicked, this, &MainWindow::onResumeClicked);

    // Connect signals from the delivery manager to update the GUI.
    connect(deliveryManager, &InsulinDeliveryManager::logEvent, this, &MainWindow::updateLog);
    connect(deliveryManager, &InsulinDeliveryManager::deliveryStarted, this, &MainWindow::onDeliveryStarted);
    connect(deliveryManager, &InsulinDeliveryManager::deliveryStopped, this, &MainWindow::onDeliveryStopped);
    connect(deliveryManager, &InsulinDeliveryManager::deliveryResumed, this, &MainWindow::onDeliveryResumed);
    connect(deliveryManager, &InsulinDeliveryManager::errorOccurred, this, &MainWindow::onErrorOccurred);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onStartClicked() {
    deliveryManager->startDelivery();
}

void MainWindow::onStopClicked() {
    deliveryManager->stopDelivery();
}

void MainWindow::onResumeClicked() {
    deliveryManager->resumeDelivery();
}

void MainWindow::updateLog(const QString &msg) {
    ui->textEditLog->append(msg);
    // Optionally, update dynamic information such as insulin remaining.
    // Assuming you add a getter in your InsulinDeliveryManager:
    ui->labelInsulinRemaining->setText(QString::number(deliveryManager->getInsulinRemaining(), 'f', 2) + " U");
}

void MainWindow::onDeliveryStarted() {
    ui->labelStatus->setText("Running");
}

void MainWindow::onDeliveryStopped() {
    ui->labelStatus->setText("Paused");
}

void MainWindow::onDeliveryResumed() {
    ui->labelStatus->setText("Running");
}

void MainWindow::onErrorOccurred(const QString &errorMsg) {
    ui->labelStatus->setText("Error");
    QMessageBox::warning(this, "Error", errorMsg);
    ui->textEditLog->append("Error: " + errorMsg);
}

