#include "OptionsPage.h"
#include "ui_OptionsPage.h"

OptionsPage::OptionsPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::OptionsPage)
{
    ui->setupUi(this);
    connect(ui->btnLoadCartridge,    &QPushButton::clicked,
            this, &OptionsPage::onBtnLoadCartridgeClicked);
    connect(ui->btnStartStopInsulin, &QPushButton::clicked,
            this, &OptionsPage::onBtnStartStopInsulinClicked);
}

OptionsPage::~OptionsPage()
{
    delete ui;
}

void OptionsPage::onBtnLoadCartridgeClicked()
{
    emit loadCartridge();
}

void OptionsPage::onBtnStartStopInsulinClicked()
{
    emit startStopInsulin();
}
