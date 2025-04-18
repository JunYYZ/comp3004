#include "ProfileListPage.h"
#include "ui_ProfileListPage.h"

ProfileListPage::ProfileListPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ProfileListPage)
{
    ui->setupUi(this);

    connect(ui->btnAdd,    &QPushButton::clicked, this, &ProfileListPage::onBtnAddClicked);
    connect(ui->btnDelete, &QPushButton::clicked, this, &ProfileListPage::onBtnDeleteClicked);
    connect(ui->btnEdit,   &QPushButton::clicked, this, &ProfileListPage::onBtnEditClicked);
}

ProfileListPage::~ProfileListPage()
{
    delete ui;
}

void ProfileListPage::setProfiles(const QStringList &names)
{
    ui->listProfiles->clear();
    ui->listProfiles->addItems(names);
}

void ProfileListPage::onBtnAddClicked()
{
    emit addProfile();
}

void ProfileListPage::onBtnDeleteClicked()
{
    auto item = ui->listProfiles->currentItem();
    if (!item) return;
    emit deleteProfile(item->text());
}

void ProfileListPage::onBtnEditClicked()
{
    auto item = ui->listProfiles->currentItem();
    if (!item) return;
    emit editProfile(item->text());
}
