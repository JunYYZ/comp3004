#include "HomePage.h"
#include "ui_HomePage.h"
#include <QPushButton>

HomePage::HomePage(QWidget *parent)
  : QWidget(parent),
    ui(new Ui::HomePage)
{
    ui->setupUi(this);

    connect(ui->btnBolus,          &QPushButton::clicked, this, &HomePage::gotoBolus);
    connect(ui->btnControlIQ,      &QPushButton::clicked, this, &HomePage::gotoControlIQ);
    connect(ui->btnGraph,          &QPushButton::clicked, this, &HomePage::gotoGraph);
    connect(ui->btnHistory,        &QPushButton::clicked, this, &HomePage::gotoHistory);
    connect(ui->btnInsulin,        &QPushButton::clicked, this, &HomePage::gotoInsulin);
    connect(ui->btnLoadCartridge,  &QPushButton::clicked, this, &HomePage::loadCartridge);
    connect(ui->btnProfiles,       &QPushButton::clicked, this, &HomePage::gotoProfiles);
    connect(ui->btnPumpInfo,       &QPushButton::clicked, this, &HomePage::gotoPumpInfo);
    connect(ui->btnSettings,       &QPushButton::clicked, this, &HomePage::gotoSettings);
    connect(ui->btnStatus,         &QPushButton::clicked, this, &HomePage::gotoStatus);
}

HomePage::~HomePage()
{
    delete ui;
}
