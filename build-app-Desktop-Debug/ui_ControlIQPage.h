/********************************************************************************
** Form generated from reading UI file 'ControlIQPage.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONTROLIQPAGE_H
#define UI_CONTROLIQPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ControlIQPage
{
public:
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *lblIQ;
    QLabel *lblNextAdjustment;
    QLabel *lblPredictedBG;
    QLabel *lblCurrentBasal;
    QLabel *lblIQStatusVal;
    QLabel *lblCurrentBasalVal;
    QLabel *lblPredictedBGVal;
    QLabel *lblNextAdjustmentVal;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnToggleCIQ;
    QPushButton *btnBackCIQ;

    void setupUi(QWidget *ControlIQPage)
    {
        if (ControlIQPage->objectName().isEmpty())
            ControlIQPage->setObjectName(QString::fromUtf8("ControlIQPage"));
        ControlIQPage->resize(733, 334);
        formLayoutWidget = new QWidget(ControlIQPage);
        formLayoutWidget->setObjectName(QString::fromUtf8("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(210, 40, 461, 221));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        lblIQ = new QLabel(formLayoutWidget);
        lblIQ->setObjectName(QString::fromUtf8("lblIQ"));

        formLayout->setWidget(0, QFormLayout::LabelRole, lblIQ);

        lblNextAdjustment = new QLabel(formLayoutWidget);
        lblNextAdjustment->setObjectName(QString::fromUtf8("lblNextAdjustment"));

        formLayout->setWidget(3, QFormLayout::LabelRole, lblNextAdjustment);

        lblPredictedBG = new QLabel(formLayoutWidget);
        lblPredictedBG->setObjectName(QString::fromUtf8("lblPredictedBG"));

        formLayout->setWidget(2, QFormLayout::LabelRole, lblPredictedBG);

        lblCurrentBasal = new QLabel(formLayoutWidget);
        lblCurrentBasal->setObjectName(QString::fromUtf8("lblCurrentBasal"));

        formLayout->setWidget(1, QFormLayout::LabelRole, lblCurrentBasal);

        lblIQStatusVal = new QLabel(formLayoutWidget);
        lblIQStatusVal->setObjectName(QString::fromUtf8("lblIQStatusVal"));

        formLayout->setWidget(0, QFormLayout::FieldRole, lblIQStatusVal);

        lblCurrentBasalVal = new QLabel(formLayoutWidget);
        lblCurrentBasalVal->setObjectName(QString::fromUtf8("lblCurrentBasalVal"));

        formLayout->setWidget(1, QFormLayout::FieldRole, lblCurrentBasalVal);

        lblPredictedBGVal = new QLabel(formLayoutWidget);
        lblPredictedBGVal->setObjectName(QString::fromUtf8("lblPredictedBGVal"));

        formLayout->setWidget(2, QFormLayout::FieldRole, lblPredictedBGVal);

        lblNextAdjustmentVal = new QLabel(formLayoutWidget);
        lblNextAdjustmentVal->setObjectName(QString::fromUtf8("lblNextAdjustmentVal"));

        formLayout->setWidget(3, QFormLayout::FieldRole, lblNextAdjustmentVal);

        horizontalLayoutWidget = new QWidget(ControlIQPage);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(400, 270, 271, 41));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        btnToggleCIQ = new QPushButton(horizontalLayoutWidget);
        btnToggleCIQ->setObjectName(QString::fromUtf8("btnToggleCIQ"));

        horizontalLayout->addWidget(btnToggleCIQ);

        btnBackCIQ = new QPushButton(horizontalLayoutWidget);
        btnBackCIQ->setObjectName(QString::fromUtf8("btnBackCIQ"));

        horizontalLayout->addWidget(btnBackCIQ);


        retranslateUi(ControlIQPage);

        QMetaObject::connectSlotsByName(ControlIQPage);
    } // setupUi

    void retranslateUi(QWidget *ControlIQPage)
    {
        ControlIQPage->setWindowTitle(QCoreApplication::translate("ControlIQPage", "Form", nullptr));
        lblIQ->setText(QCoreApplication::translate("ControlIQPage", "Control-IQ Status:", nullptr));
        lblNextAdjustment->setText(QCoreApplication::translate("ControlIQPage", "Next Automated Adjustment:", nullptr));
        lblPredictedBG->setText(QCoreApplication::translate("ControlIQPage", "Predicted BG (30 min):", nullptr));
        lblCurrentBasal->setText(QCoreApplication::translate("ControlIQPage", "Current Basal Rate (U/hr):", nullptr));
        lblIQStatusVal->setText(QCoreApplication::translate("ControlIQPage", "Active", nullptr));
        lblCurrentBasalVal->setText(QString());
        lblPredictedBGVal->setText(QString());
        lblNextAdjustmentVal->setText(QString());
        btnToggleCIQ->setText(QCoreApplication::translate("ControlIQPage", "On/Off", nullptr));
        btnBackCIQ->setText(QCoreApplication::translate("ControlIQPage", "Back", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ControlIQPage: public Ui_ControlIQPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONTROLIQPAGE_H
