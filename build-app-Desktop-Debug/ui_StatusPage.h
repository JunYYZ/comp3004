/********************************************************************************
** Form generated from reading UI file 'StatusPage.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STATUSPAGE_H
#define UI_STATUSPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StatusPage
{
public:
    QSplitter *splitter;
    QLabel *lblBG;
    QLabel *lblIOB;
    QLabel *lblBasal;
    QLabel *lblBattery;
    QSplitter *splitter_2;
    QLabel *valBG;
    QLabel *valIOB;
    QLabel *valBasal;
    QProgressBar *barBattery;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnStart;
    QPushButton *btnStop;

    void setupUi(QWidget *StatusPage)
    {
        if (StatusPage->objectName().isEmpty())
            StatusPage->setObjectName(QString::fromUtf8("StatusPage"));
        StatusPage->resize(733, 334);
        splitter = new QSplitter(StatusPage);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setGeometry(QRect(230, 70, 161, 161));
        splitter->setOrientation(Qt::Vertical);
        lblBG = new QLabel(splitter);
        lblBG->setObjectName(QString::fromUtf8("lblBG"));
        splitter->addWidget(lblBG);
        lblIOB = new QLabel(splitter);
        lblIOB->setObjectName(QString::fromUtf8("lblIOB"));
        splitter->addWidget(lblIOB);
        lblBasal = new QLabel(splitter);
        lblBasal->setObjectName(QString::fromUtf8("lblBasal"));
        splitter->addWidget(lblBasal);
        lblBattery = new QLabel(splitter);
        lblBattery->setObjectName(QString::fromUtf8("lblBattery"));
        splitter->addWidget(lblBattery);
        splitter_2 = new QSplitter(StatusPage);
        splitter_2->setObjectName(QString::fromUtf8("splitter_2"));
        splitter_2->setGeometry(QRect(480, 70, 151, 161));
        splitter_2->setOrientation(Qt::Vertical);
        valBG = new QLabel(splitter_2);
        valBG->setObjectName(QString::fromUtf8("valBG"));
        splitter_2->addWidget(valBG);
        valIOB = new QLabel(splitter_2);
        valIOB->setObjectName(QString::fromUtf8("valIOB"));
        splitter_2->addWidget(valIOB);
        valBasal = new QLabel(splitter_2);
        valBasal->setObjectName(QString::fromUtf8("valBasal"));
        splitter_2->addWidget(valBasal);
        barBattery = new QProgressBar(splitter_2);
        barBattery->setObjectName(QString::fromUtf8("barBattery"));
        barBattery->setValue(24);
        splitter_2->addWidget(barBattery);
        layoutWidget = new QWidget(StatusPage);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(260, 270, 341, 27));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        btnStart = new QPushButton(layoutWidget);
        btnStart->setObjectName(QString::fromUtf8("btnStart"));

        horizontalLayout->addWidget(btnStart);

        btnStop = new QPushButton(layoutWidget);
        btnStop->setObjectName(QString::fromUtf8("btnStop"));

        horizontalLayout->addWidget(btnStop);


        retranslateUi(StatusPage);

        QMetaObject::connectSlotsByName(StatusPage);
    } // setupUi

    void retranslateUi(QWidget *StatusPage)
    {
        StatusPage->setWindowTitle(QCoreApplication::translate("StatusPage", "Form", nullptr));
        lblBG->setText(QCoreApplication::translate("StatusPage", "Current BG (mmol/L):", nullptr));
        lblIOB->setText(QCoreApplication::translate("StatusPage", "Insulin On Board (U):", nullptr));
        lblBasal->setText(QCoreApplication::translate("StatusPage", "Basal Rate (U/hr):", nullptr));
        lblBattery->setText(QCoreApplication::translate("StatusPage", "Battery Level (%):", nullptr));
        valBG->setText(QString());
        valIOB->setText(QString());
        valBasal->setText(QString());
        btnStart->setText(QCoreApplication::translate("StatusPage", "Start Basal", nullptr));
        btnStop->setText(QCoreApplication::translate("StatusPage", "Stop Basal", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StatusPage: public Ui_StatusPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STATUSPAGE_H
