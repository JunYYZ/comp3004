// ControlIQPage.cpp
#include "ControlIQPage.h"
#include "ui_ControlIQPage.h"

ControlIQPage::ControlIQPage(QWidget *parent)
  : QWidget(parent), ui(new Ui::ControlIQPage)
{
    ui->setupUi(this);
    connect(ui->btnToggleCIQ, &QPushButton::clicked, this, &ControlIQPage::on_btnToggleCIQ_clicked);
    connect(ui->btnBackCIQ,   &QPushButton::clicked, this, &ControlIQPage::on_btnBackCIQ_clicked);
}

ControlIQPage::~ControlIQPage()
{
    delete ui;
}

void ControlIQPage::setStatus(const QString &status)
{
    ui->lblIQStatusVal->setText(status);
    ui->btnToggleCIQ->setText(status == "Active" ? "Turn Off" : "Turn On");
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

void ControlIQPage::on_btnToggleCIQ_clicked()
{
    emit toggleClicked();
}

void ControlIQPage::on_btnBackCIQ_clicked()
{
    emit backClicked();
}
