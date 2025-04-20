/********************************************************************************
** Form generated from reading UI file 'SettingsPage.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGSPAGE_H
#define UI_SETTINGSPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SettingsPage
{
public:
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *lblMaxBolus;
    QLabel *lblLowInsulin;
    QLabel *lblHighBGAlarm;
    QLabel *lblLowBGAlarm;
    QLabel *lblMinBasal;
    QLabel *lblMaxBasal;
    QDoubleSpinBox *sbMaxBolus;
    QDoubleSpinBox *sbMaxBasal;
    QDoubleSpinBox *sbMinBasal;
    QSpinBox *sbLowBGAlarm;
    QSpinBox *sbHighBGAlarm;
    QDoubleSpinBox *sbLowInsulin;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnSave;
    QPushButton *btnCancel;

    void setupUi(QWidget *SettingsPage)
    {
        if (SettingsPage->objectName().isEmpty())
            SettingsPage->setObjectName(QString::fromUtf8("SettingsPage"));
        SettingsPage->resize(733, 334);
        widget = new QWidget(SettingsPage);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(210, 30, 501, 261));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        lblMaxBolus = new QLabel(widget);
        lblMaxBolus->setObjectName(QString::fromUtf8("lblMaxBolus"));

        formLayout->setWidget(0, QFormLayout::LabelRole, lblMaxBolus);

        lblLowInsulin = new QLabel(widget);
        lblLowInsulin->setObjectName(QString::fromUtf8("lblLowInsulin"));

        formLayout->setWidget(5, QFormLayout::LabelRole, lblLowInsulin);

        lblHighBGAlarm = new QLabel(widget);
        lblHighBGAlarm->setObjectName(QString::fromUtf8("lblHighBGAlarm"));

        formLayout->setWidget(4, QFormLayout::LabelRole, lblHighBGAlarm);

        lblLowBGAlarm = new QLabel(widget);
        lblLowBGAlarm->setObjectName(QString::fromUtf8("lblLowBGAlarm"));

        formLayout->setWidget(3, QFormLayout::LabelRole, lblLowBGAlarm);

        lblMinBasal = new QLabel(widget);
        lblMinBasal->setObjectName(QString::fromUtf8("lblMinBasal"));

        formLayout->setWidget(2, QFormLayout::LabelRole, lblMinBasal);

        lblMaxBasal = new QLabel(widget);
        lblMaxBasal->setObjectName(QString::fromUtf8("lblMaxBasal"));

        formLayout->setWidget(1, QFormLayout::LabelRole, lblMaxBasal);

        sbMaxBolus = new QDoubleSpinBox(widget);
        sbMaxBolus->setObjectName(QString::fromUtf8("sbMaxBolus"));
        sbMaxBolus->setDecimals(1);
        sbMaxBolus->setMinimum(0.000000000000000);
        sbMaxBolus->setSingleStep(0.100000000000000);
        sbMaxBolus->setValue(0.000000000000000);

        formLayout->setWidget(0, QFormLayout::FieldRole, sbMaxBolus);

        sbMaxBasal = new QDoubleSpinBox(widget);
        sbMaxBasal->setObjectName(QString::fromUtf8("sbMaxBasal"));
        sbMaxBasal->setMaximum(10.000000000000000);
        sbMaxBasal->setSingleStep(0.010000000000000);

        formLayout->setWidget(1, QFormLayout::FieldRole, sbMaxBasal);

        sbMinBasal = new QDoubleSpinBox(widget);
        sbMinBasal->setObjectName(QString::fromUtf8("sbMinBasal"));
        sbMinBasal->setMaximum(10.000000000000000);
        sbMinBasal->setSingleStep(0.010000000000000);

        formLayout->setWidget(2, QFormLayout::FieldRole, sbMinBasal);

        sbLowBGAlarm = new QSpinBox(widget);
        sbLowBGAlarm->setObjectName(QString::fromUtf8("sbLowBGAlarm"));
        sbLowBGAlarm->setMinimum(1);
        sbLowBGAlarm->setMaximum(10);

        formLayout->setWidget(3, QFormLayout::FieldRole, sbLowBGAlarm);

        sbHighBGAlarm = new QSpinBox(widget);
        sbHighBGAlarm->setObjectName(QString::fromUtf8("sbHighBGAlarm"));
        sbHighBGAlarm->setMinimum(5);
        sbHighBGAlarm->setMaximum(25);

        formLayout->setWidget(4, QFormLayout::FieldRole, sbHighBGAlarm);

        sbLowInsulin = new QDoubleSpinBox(widget);
        sbLowInsulin->setObjectName(QString::fromUtf8("sbLowInsulin"));
        sbLowInsulin->setDecimals(1);
        sbLowInsulin->setMaximum(50.000000000000000);
        sbLowInsulin->setSingleStep(0.100000000000000);

        formLayout->setWidget(5, QFormLayout::FieldRole, sbLowInsulin);


        verticalLayout->addLayout(formLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        btnSave = new QPushButton(widget);
        btnSave->setObjectName(QString::fromUtf8("btnSave"));

        horizontalLayout->addWidget(btnSave);

        btnCancel = new QPushButton(widget);
        btnCancel->setObjectName(QString::fromUtf8("btnCancel"));

        horizontalLayout->addWidget(btnCancel);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(SettingsPage);

        QMetaObject::connectSlotsByName(SettingsPage);
    } // setupUi

    void retranslateUi(QWidget *SettingsPage)
    {
        SettingsPage->setWindowTitle(QCoreApplication::translate("SettingsPage", "Form", nullptr));
        lblMaxBolus->setText(QCoreApplication::translate("SettingsPage", "Max Bolus (U):", nullptr));
        lblLowInsulin->setText(QCoreApplication::translate("SettingsPage", "Low Insulin Alert (U):", nullptr));
        lblHighBGAlarm->setText(QCoreApplication::translate("SettingsPage", "High BG Alarm (mmol/L):", nullptr));
        lblLowBGAlarm->setText(QCoreApplication::translate("SettingsPage", "Low BG Alarm (mmol/L):", nullptr));
        lblMinBasal->setText(QCoreApplication::translate("SettingsPage", "Min Basal Rate (U/hr):", nullptr));
        lblMaxBasal->setText(QCoreApplication::translate("SettingsPage", "Max Basal Rate (U/hr):", nullptr));
        btnSave->setText(QCoreApplication::translate("SettingsPage", "Save", nullptr));
        btnCancel->setText(QCoreApplication::translate("SettingsPage", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingsPage: public Ui_SettingsPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGSPAGE_H
