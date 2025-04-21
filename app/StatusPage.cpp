#include "StatusPage.h"
#include "ui_StatusPage.h"

StatusPage::StatusPage(QWidget *parent)
  : QWidget(parent),
    ui(new Ui::StatusPage)
{
    ui->setupUi(this);

   connect(ui->btnBack,  &QPushButton::clicked, this, &StatusPage::backRequested);
}

StatusPage::~StatusPage()
{
    delete ui;
}

void StatusPage::setCurrentBG(double bg) {
    ui->valBG->setText(QString::number(bg, 'f', 1));
}

void StatusPage::setInsulinOnBoard(double iob) {
    ui->valIOB->setText(QString::number(iob, 'f', 1));
}

void StatusPage::setBasalRate(double rate) {
    ui->valBasal->setText(QString::number(rate, 'f', 2));
}

