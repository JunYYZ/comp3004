// ControlIQPage.cpp
#include "ControlIQPage.h"
#include "ui_ControlIQPage.h"

ControlIQPage::ControlIQPage(QWidget *parent)
  : QWidget(parent), ui(new Ui::ControlIQPage)
{
    ui->setupUi(this);

    // Connect the UI buttons to our signals
    connect(ui->btnTurnOn, &QPushButton::clicked, this, &ControlIQPage::on_btnTurnOnCIQ_clicked);
    connect(ui->btnTurnOff, &QPushButton::clicked, this, &ControlIQPage::on_btnTurnOffCIQ_clicked);
    connect(ui->btnBackCIQ, &QPushButton::clicked, this, &ControlIQPage::on_btnBackCIQ_clicked);
}


ControlIQPage::~ControlIQPage()
{
    delete ui;
}

void ControlIQPage::setStatus(const QString &status)
{
    ui->lblIQStatusVal->setText(status);
    // Update button texts when the status changes
    ui->btnTurnOn->setText(status == "Active" ? "ControlIQ is Active" : "Turn On");
    ui->btnTurnOff->setText(status == "Inactive" ? "ControlIQ is Inactive" : "Turn Off");
}

void ControlIQPage::setCurrentBasal(double rate)
{
    ui->lblCurrentBasalVal->setText(QString::number(rate, 'f', 2) + " U/hr");
}

void ControlIQPage::setPredictedBG(double bg)
{
    ui->lblPredictedBGVal->setText(QString::number(bg, 'f', 1) + " mmol/L");
}

void ControlIQPage::setNextAdjustment(const QString &adj)
{
    ui->lblNextAdjustmentVal->setText(adj);
}

void ControlIQPage::on_btnTurnOnCIQ_clicked()
{
    emit controlIQTurnedOn();  // Emit signal to enable ControlIQ
}

void ControlIQPage::on_btnTurnOffCIQ_clicked()
{
    emit controlIQTurnedOff();  // Emit signal to disable ControlIQ
}

void ControlIQPage::on_btnBackCIQ_clicked()
{
    emit backClicked();
}
