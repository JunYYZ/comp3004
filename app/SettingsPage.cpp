#include "SettingsPage.h"
#include "ui_SettingsPage.h"

SettingsPage::SettingsPage(QWidget *parent)
  : QWidget(parent),
    ui(new Ui::SettingsPage)
{
    ui->setupUi(this);

    // Wire buttons to our own signals
    connect(ui->btnSave,   &QPushButton::clicked, this, &SettingsPage::on_btnSave_clicked);
    connect(ui->btnCancel, &QPushButton::clicked, this, &SettingsPage::on_btnCancel_clicked);
}

SettingsPage::~SettingsPage()
{
    delete ui;
}

void SettingsPage::loadSettings(const PumpSettings &s)
{
    ui->sbMaxBolus->setValue(s.maxBolus);
    ui->sbMaxBasal->setValue(s.maxBasal);
    ui->sbMinBasal->setValue(s.minBasal);
    ui->sbLowBGAlarm->setValue(s.lowBGAlarm);
    ui->sbHighBGAlarm->setValue(s.highBGAlarm);
    ui->sbLowInsulin->setValue(s.lowInsulinAlert);
}

PumpSettings SettingsPage::currentSettings() const
{
    PumpSettings s;
    s.maxBolus         = ui->sbMaxBolus->value();
    s.maxBasal         = ui->sbMaxBasal->value();
    s.minBasal         = ui->sbMinBasal->value();
    s.lowBGAlarm       = ui->sbLowBGAlarm->value();
    s.highBGAlarm      = ui->sbHighBGAlarm->value();
    s.lowInsulinAlert  = ui->sbLowInsulin->value();
    return s;
}

void SettingsPage::on_btnSave_clicked()
{
    emit saveClicked();
}

void SettingsPage::on_btnCancel_clicked()
{
    emit backRequested();
}
