#include "ProfileEditorPage.h"
#include "ui_ProfileEditorPage.h"
#include "ProfileManager.h"

#include <QPushButton>

ProfileEditorPage::ProfileEditorPage(ProfileManager* manager, QWidget *parent)
  : QWidget(parent)
  , ui(new Ui::ProfileEditorPage)
  , m_profileManager(manager)
  , m_current("", 1.0, 1.0, 0)
  , m_mode(Mode::New)
{
    ui->setupUi(this);
    connect(ui->btnSave,   &QPushButton::clicked, this, &ProfileEditorPage::onBtnSaveClicked);
    connect(ui->btnCancel, &QPushButton::clicked, this, &ProfileEditorPage::onBtnCancelClicked);
    updateUiForMode();
}

ProfileEditorPage::ProfileEditorPage(QWidget *parent)
  : QWidget(parent)
  , ui(new Ui::ProfileEditorPage)
  , m_profileManager(nullptr)
  , m_current("", 1.0, 1.0, 0)
  , m_mode(Mode::New)
{
    ui->setupUi(this);
    connect(ui->btnSave,   &QPushButton::clicked, this, &ProfileEditorPage::onBtnSaveClicked);
    connect(ui->btnCancel, &QPushButton::clicked, this, &ProfileEditorPage::onBtnCancelClicked);
    updateUiForMode();
}

ProfileEditorPage::~ProfileEditorPage()
{
    delete ui;
}

void ProfileEditorPage::setProfileManager(ProfileManager* mgr)
{
    m_profileManager = mgr;
}

void ProfileEditorPage::setMode(Mode m)
{
    m_mode = m;
    updateUiForMode();
}

ProfileEditorPage::Mode ProfileEditorPage::mode() const
{
    return m_mode;
}

void ProfileEditorPage::setProfile(const Profile &p)
{
    m_current = p;
    m_originalName = p.name();
    // preload UI fields
    loadProfileIntoUi();
    // switch into edit mode
    setMode(Mode::Edit);
}

void ProfileEditorPage::loadProfileIntoUi()
{
    ui->leName      ->setText(m_current.name());
    ui->sbCarbRatio ->setValue(m_current.carbRatio());
    ui->sbCorrection->setValue(m_current.correctionFactor());
    ui->sbTargetBG  ->setValue(m_current.targetBG());
}

void ProfileEditorPage::collectUiIntoProfile()
{
    m_current.setName(           ui->leName      ->text());
    m_current.setCarbRatio(      ui->sbCarbRatio ->value());
    m_current.setCorrectionFactor(ui->sbCorrection->value());
    m_current.setTargetBG(       ui->sbTargetBG  ->value());
}

void ProfileEditorPage::updateUiForMode()
{
    switch (m_mode) {
      case Mode::New:
        ui->btnSave->setText(tr("Add Profile"));
        break;
      case Mode::Edit:
        ui->btnSave->setText(tr("Update Profile"));
        break;
    }
}

void ProfileEditorPage::onBtnSaveClicked()
{
    collectUiIntoProfile();

    if (!m_profileManager) {
        // shouldn’t happen – you need to have injected it
        return;
    }

    if (m_mode == Mode::New) {
        emit addProfile(m_current);
    } else {
        emit updateProfile(m_originalName, m_current);
    }
}

void ProfileEditorPage::onBtnCancelClicked()
{
    emit cancel();
}
