#include "PumpInfoPage.h"
#include "ui_PumpInfoPage.h"

PumpInfoPage::PumpInfoPage(QWidget *parent)
  : QWidget(parent),
    ui(new Ui::PumpInfoPage)
{
    ui->setupUi(this);

    connect(ui->btnBackInfo, &QPushButton::clicked,
            this, &PumpInfoPage::on_btnBackInfo_clicked);
}

PumpInfoPage::~PumpInfoPage()
{
    delete ui;
}

void PumpInfoPage::setSerial(const QString &serial)
{
    ui->lblSerialVal->setText(serial);
}

void PumpInfoPage::setSoftwareVersion(const QString &ver)
{
    ui->lblSWVal->setText(ver);
}

void PumpInfoPage::setFirmwareVersion(const QString &ver)
{
    ui->lblFWVal->setText(ver);
}

void PumpInfoPage::on_btnBackInfo_clicked()
{
    emit backClicked();
}
