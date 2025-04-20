/********************************************************************************
** Form generated from reading UI file 'PumpInfoPage.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PUMPINFOPAGE_H
#define UI_PUMPINFOPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PumpInfoPage
{
public:
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *lblSerial;
    QLabel *lblCGM;
    QLabel *lblBattery;
    QLabel *lblSW;
    QLabel *lblInsulin;
    QLabel *lblFW;
    QLabel *lblSerialVal;
    QLabel *lblSWVal;
    QLabel *lblFWVal;
    QLabel *lblCGMVal;
    QProgressBar *barInsulinVal;
    QProgressBar *barBatteryVal;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnBackInfo;

    void setupUi(QWidget *PumpInfoPage)
    {
        if (PumpInfoPage->objectName().isEmpty())
            PumpInfoPage->setObjectName(QString::fromUtf8("PumpInfoPage"));
        PumpInfoPage->resize(733, 334);
        formLayoutWidget = new QWidget(PumpInfoPage);
        formLayoutWidget->setObjectName(QString::fromUtf8("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(99, 39, 501, 221));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        lblSerial = new QLabel(formLayoutWidget);
        lblSerial->setObjectName(QString::fromUtf8("lblSerial"));

        formLayout->setWidget(0, QFormLayout::LabelRole, lblSerial);

        lblCGM = new QLabel(formLayoutWidget);
        lblCGM->setObjectName(QString::fromUtf8("lblCGM"));

        formLayout->setWidget(5, QFormLayout::LabelRole, lblCGM);

        lblBattery = new QLabel(formLayoutWidget);
        lblBattery->setObjectName(QString::fromUtf8("lblBattery"));

        formLayout->setWidget(4, QFormLayout::LabelRole, lblBattery);

        lblSW = new QLabel(formLayoutWidget);
        lblSW->setObjectName(QString::fromUtf8("lblSW"));

        formLayout->setWidget(1, QFormLayout::LabelRole, lblSW);

        lblInsulin = new QLabel(formLayoutWidget);
        lblInsulin->setObjectName(QString::fromUtf8("lblInsulin"));

        formLayout->setWidget(3, QFormLayout::LabelRole, lblInsulin);

        lblFW = new QLabel(formLayoutWidget);
        lblFW->setObjectName(QString::fromUtf8("lblFW"));

        formLayout->setWidget(2, QFormLayout::LabelRole, lblFW);

        lblSerialVal = new QLabel(formLayoutWidget);
        lblSerialVal->setObjectName(QString::fromUtf8("lblSerialVal"));

        formLayout->setWidget(0, QFormLayout::FieldRole, lblSerialVal);

        lblSWVal = new QLabel(formLayoutWidget);
        lblSWVal->setObjectName(QString::fromUtf8("lblSWVal"));

        formLayout->setWidget(1, QFormLayout::FieldRole, lblSWVal);

        lblFWVal = new QLabel(formLayoutWidget);
        lblFWVal->setObjectName(QString::fromUtf8("lblFWVal"));

        formLayout->setWidget(2, QFormLayout::FieldRole, lblFWVal);

        lblCGMVal = new QLabel(formLayoutWidget);
        lblCGMVal->setObjectName(QString::fromUtf8("lblCGMVal"));

        formLayout->setWidget(5, QFormLayout::FieldRole, lblCGMVal);

        barInsulinVal = new QProgressBar(formLayoutWidget);
        barInsulinVal->setObjectName(QString::fromUtf8("barInsulinVal"));
        barInsulinVal->setValue(24);

        formLayout->setWidget(3, QFormLayout::FieldRole, barInsulinVal);

        barBatteryVal = new QProgressBar(formLayoutWidget);
        barBatteryVal->setObjectName(QString::fromUtf8("barBatteryVal"));
        barBatteryVal->setValue(24);

        formLayout->setWidget(4, QFormLayout::FieldRole, barBatteryVal);

        horizontalLayoutWidget = new QWidget(PumpInfoPage);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(450, 270, 151, 41));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        btnBackInfo = new QPushButton(horizontalLayoutWidget);
        btnBackInfo->setObjectName(QString::fromUtf8("btnBackInfo"));

        horizontalLayout->addWidget(btnBackInfo);


        retranslateUi(PumpInfoPage);

        QMetaObject::connectSlotsByName(PumpInfoPage);
    } // setupUi

    void retranslateUi(QWidget *PumpInfoPage)
    {
        PumpInfoPage->setWindowTitle(QCoreApplication::translate("PumpInfoPage", "Form", nullptr));
        lblSerial->setText(QCoreApplication::translate("PumpInfoPage", "Pump Serial #:", nullptr));
        lblCGM->setText(QCoreApplication::translate("PumpInfoPage", "CGM Status:", nullptr));
        lblBattery->setText(QCoreApplication::translate("PumpInfoPage", "Battery Level (%):", nullptr));
        lblSW->setText(QCoreApplication::translate("PumpInfoPage", "Software Version:", nullptr));
        lblInsulin->setText(QCoreApplication::translate("PumpInfoPage", "Insulin Remaining (U):", nullptr));
        lblFW->setText(QCoreApplication::translate("PumpInfoPage", "Firmware Version:", nullptr));
        lblSerialVal->setText(QCoreApplication::translate("PumpInfoPage", "12345678910", nullptr));
        lblSWVal->setText(QCoreApplication::translate("PumpInfoPage", "3.7.1", nullptr));
        lblFWVal->setText(QCoreApplication::translate("PumpInfoPage", "3.5.1", nullptr));
        lblCGMVal->setText(QCoreApplication::translate("PumpInfoPage", "Connected", nullptr));
        btnBackInfo->setText(QCoreApplication::translate("PumpInfoPage", "Back", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PumpInfoPage: public Ui_PumpInfoPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PUMPINFOPAGE_H
