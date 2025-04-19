#include "ProfileListPage.h"
#include "ui_ProfileListPage.h"
#include "ProfileManager.h"

#include <QPushButton>
#include <QListWidgetItem>

ProfileListPage::ProfileListPage(QWidget *parent)
  : QWidget(parent),
    ui(new Ui::ProfileListPage)
{
    ui->setupUi(this);

    // wire up buttons to our own slots
    connect(ui->btnAdd,    &QPushButton::clicked, this, &ProfileListPage::onBtnAddClicked);
    connect(ui->btnEdit,   &QPushButton::clicked, this, &ProfileListPage::onBtnEditClicked);
    connect(ui->btnDelete, &QPushButton::clicked, this, &ProfileListPage::onBtnDeleteClicked);
}

ProfileListPage::~ProfileListPage()
{
    delete ui;
}

void ProfileListPage::setProfileManager(ProfileManager* mgr)
{
    // store it
    m_profileManager = mgr;

    // whenever the manager’s data changes, we refresh
    connect(m_profileManager,
            &ProfileManager::profileChanged,
            this,
            &ProfileListPage::refreshProfiles,
            Qt::UniqueConnection);

    // initial fill
    refreshProfiles();
}

void ProfileListPage::refreshProfiles()
{
    ui->listProfiles->clear();
    if (!m_profileManager) return;

    // pull the names out of the manager
    QStringList names;
    for (const auto &p : m_profileManager->profiles())
        names << p.name();

    ui->listProfiles->addItems(names);
}

void ProfileListPage::onBtnAddClicked()
{
    emit requestAddProfile();
}

void ProfileListPage::onBtnEditClicked()
{
    auto *item = ui->listProfiles->currentItem();
    if (!item) return;
    emit requestEditProfile(item->text());
}

void ProfileListPage::onBtnDeleteClicked()
{
    auto *item = ui->listProfiles->currentItem();
    if (!item) return;
    emit requestDeleteProfile(item->text());
}
