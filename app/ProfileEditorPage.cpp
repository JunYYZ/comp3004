#include "ProfileEditorPage.h"
#include "ui_ProfileEditorPage.h"

ProfileEditorPage::ProfileEditorPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ProfileEditorPage)
{
    ui->setupUi(this);
    connect(ui->btnSave,   &QPushButton::clicked, this, &ProfileEditorPage::onBtnSaveClicked);
    connect(ui->btnCancel, &QPushButton::clicked, this, &ProfileEditorPage::onBtnCancelClicked);
}

ProfileEditorPage::~ProfileEditorPage()
{
    delete ui;
}

void ProfileEditorPage::setProfile(const Profile &p)
{
    m_current = p;
    ui->lblName->setText(p.name());
    ui->sbCarbRatio->setValue(p.carbRatio());
    ui->sbCorrection->setValue(p.correctionFactor());
    ui->sbTargetBG->setValue(p.targetBG());
}

void ProfileEditorPage::onBtnSaveClicked()
{
    Profile edited(
        ui->lblName->text(),
        ui->sbCarbRatio->value(),
        ui->sbCorrection->value(),
        ui->sbTargetBG->value()
    );
    emit saveProfile(edited);
}

void ProfileEditorPage::onBtnCancelClicked()
{
    emit cancel();
}
