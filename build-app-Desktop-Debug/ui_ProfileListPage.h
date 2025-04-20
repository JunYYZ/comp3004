/********************************************************************************
** Form generated from reading UI file 'ProfileListPage.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROFILELISTPAGE_H
#define UI_PROFILELISTPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ProfileListPage
{
public:
    QListWidget *listProfiles;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnAdd;
    QPushButton *btnActive;
    QPushButton *btnEdit;
    QPushButton *btnDelete;
    QPushButton *btnBack;

    void setupUi(QWidget *ProfileListPage)
    {
        if (ProfileListPage->objectName().isEmpty())
            ProfileListPage->setObjectName(QString::fromUtf8("ProfileListPage"));
        ProfileListPage->resize(733, 334);
        listProfiles = new QListWidget(ProfileListPage);
        listProfiles->setObjectName(QString::fromUtf8("listProfiles"));
        listProfiles->setGeometry(QRect(110, 50, 501, 191));
        horizontalLayoutWidget = new QWidget(ProfileListPage);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(150, 240, 429, 80));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        btnAdd = new QPushButton(horizontalLayoutWidget);
        btnAdd->setObjectName(QString::fromUtf8("btnAdd"));

        horizontalLayout->addWidget(btnAdd);

        btnActive = new QPushButton(horizontalLayoutWidget);
        btnActive->setObjectName(QString::fromUtf8("btnActive"));

        horizontalLayout->addWidget(btnActive);

        btnEdit = new QPushButton(horizontalLayoutWidget);
        btnEdit->setObjectName(QString::fromUtf8("btnEdit"));

        horizontalLayout->addWidget(btnEdit);

        btnDelete = new QPushButton(horizontalLayoutWidget);
        btnDelete->setObjectName(QString::fromUtf8("btnDelete"));

        horizontalLayout->addWidget(btnDelete);

        btnBack = new QPushButton(horizontalLayoutWidget);
        btnBack->setObjectName(QString::fromUtf8("btnBack"));

        horizontalLayout->addWidget(btnBack);


        retranslateUi(ProfileListPage);

        QMetaObject::connectSlotsByName(ProfileListPage);
    } // setupUi

    void retranslateUi(QWidget *ProfileListPage)
    {
        ProfileListPage->setWindowTitle(QCoreApplication::translate("ProfileListPage", "Form", nullptr));
        btnAdd->setText(QCoreApplication::translate("ProfileListPage", "Add", nullptr));
        btnActive->setText(QCoreApplication::translate("ProfileListPage", "Set Active", nullptr));
        btnEdit->setText(QCoreApplication::translate("ProfileListPage", "Edit", nullptr));
        btnDelete->setText(QCoreApplication::translate("ProfileListPage", "Delete", nullptr));
        btnBack->setText(QCoreApplication::translate("ProfileListPage", "Back", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ProfileListPage: public Ui_ProfileListPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROFILELISTPAGE_H
