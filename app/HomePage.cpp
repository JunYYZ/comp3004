#include "HomePage.h"
#include "ui_HomePage.h"
#include <QPushButton>
#include "Pump.h"

HomePage::HomePage(QWidget *parent)
  : QWidget(parent),
    ui(new Ui::HomePage)
{
    ui->setupUi(this);

    connect(ui->btnBolus,          &QPushButton::clicked, this, &HomePage::gotoBolus);
    connect(ui->btnControlIQ,      &QPushButton::clicked, this, &HomePage::gotoControlIQ);
    connect(ui->btnGraph,          &QPushButton::clicked, this, &HomePage::gotoGraph);
    connect(ui->btnHistory,        &QPushButton::clicked, this, &HomePage::gotoHistory);
    connect(ui->btnProfiles,       &QPushButton::clicked, this, &HomePage::gotoProfiles);
    connect(ui->btnSettings,       &QPushButton::clicked, this, &HomePage::gotoSettings);
}

HomePage::~HomePage()
{
    delete ui;
}

void HomePage::refreshIOB()
{
    if (!m_pump) return;
    ui->lblIOB->setText(
        QString("%1 U").arg(m_pump->getInsulinOnBoard(), 0, 'f', 2));
}

void HomePage::setIOB(double u)
{
    // format to two decimals
    ui->lblIOB->setText(QString::number(u, 'f', 2) + " U");
}



