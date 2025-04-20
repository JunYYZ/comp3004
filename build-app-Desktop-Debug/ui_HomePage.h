/********************************************************************************
** Form generated from reading UI file 'HomePage.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HOMEPAGE_H
#define UI_HOMEPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HomePage
{
public:
    QLabel *lblHomeTitle;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout_2;
    QPushButton *btnProfiles;
    QPushButton *btnControlIQ;
    QPushButton *btnStatus;
    QPushButton *btnBolus;
    QPushButton *btnSettings;
    QPushButton *btnPumpInfo;
    QPushButton *btnGraph;
    QPushButton *btnHistory;
    QPushButton *btnLoadCartridge;
    QPushButton *btnInsulin;

    void setupUi(QWidget *HomePage)
    {
        if (HomePage->objectName().isEmpty())
            HomePage->setObjectName(QString::fromUtf8("HomePage"));
        HomePage->resize(773, 340);
        lblHomeTitle = new QLabel(HomePage);
        lblHomeTitle->setObjectName(QString::fromUtf8("lblHomeTitle"));
        lblHomeTitle->setGeometry(QRect(70, 20, 151, 61));
        QFont font;
        font.setFamily(QString::fromUtf8("Liberation Sans"));
        font.setPointSize(20);
        font.setBold(true);
        font.setWeight(75);
        lblHomeTitle->setFont(font);
        gridLayoutWidget = new QWidget(HomePage);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(110, 80, 601, 191));
        gridLayout_2 = new QGridLayout(gridLayoutWidget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        btnProfiles = new QPushButton(gridLayoutWidget);
        btnProfiles->setObjectName(QString::fromUtf8("btnProfiles"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(btnProfiles->sizePolicy().hasHeightForWidth());
        btnProfiles->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(btnProfiles, 0, 0, 1, 1);

        btnControlIQ = new QPushButton(gridLayoutWidget);
        btnControlIQ->setObjectName(QString::fromUtf8("btnControlIQ"));
        sizePolicy.setHeightForWidth(btnControlIQ->sizePolicy().hasHeightForWidth());
        btnControlIQ->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(btnControlIQ, 1, 0, 1, 1);

        btnStatus = new QPushButton(gridLayoutWidget);
        btnStatus->setObjectName(QString::fromUtf8("btnStatus"));
        sizePolicy.setHeightForWidth(btnStatus->sizePolicy().hasHeightForWidth());
        btnStatus->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(btnStatus, 1, 2, 1, 1);

        btnBolus = new QPushButton(gridLayoutWidget);
        btnBolus->setObjectName(QString::fromUtf8("btnBolus"));
        sizePolicy.setHeightForWidth(btnBolus->sizePolicy().hasHeightForWidth());
        btnBolus->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(btnBolus, 1, 1, 1, 1);

        btnSettings = new QPushButton(gridLayoutWidget);
        btnSettings->setObjectName(QString::fromUtf8("btnSettings"));
        sizePolicy.setHeightForWidth(btnSettings->sizePolicy().hasHeightForWidth());
        btnSettings->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(btnSettings, 0, 2, 1, 1);

        btnPumpInfo = new QPushButton(gridLayoutWidget);
        btnPumpInfo->setObjectName(QString::fromUtf8("btnPumpInfo"));
        sizePolicy.setHeightForWidth(btnPumpInfo->sizePolicy().hasHeightForWidth());
        btnPumpInfo->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(btnPumpInfo, 0, 1, 1, 1);

        btnGraph = new QPushButton(gridLayoutWidget);
        btnGraph->setObjectName(QString::fromUtf8("btnGraph"));
        sizePolicy.setHeightForWidth(btnGraph->sizePolicy().hasHeightForWidth());
        btnGraph->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(btnGraph, 0, 3, 1, 1);

        btnHistory = new QPushButton(gridLayoutWidget);
        btnHistory->setObjectName(QString::fromUtf8("btnHistory"));
        sizePolicy.setHeightForWidth(btnHistory->sizePolicy().hasHeightForWidth());
        btnHistory->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(btnHistory, 1, 3, 1, 1);

        btnLoadCartridge = new QPushButton(gridLayoutWidget);
        btnLoadCartridge->setObjectName(QString::fromUtf8("btnLoadCartridge"));
        sizePolicy.setHeightForWidth(btnLoadCartridge->sizePolicy().hasHeightForWidth());
        btnLoadCartridge->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(btnLoadCartridge, 1, 4, 1, 1);

        btnInsulin = new QPushButton(gridLayoutWidget);
        btnInsulin->setObjectName(QString::fromUtf8("btnInsulin"));
        sizePolicy.setHeightForWidth(btnInsulin->sizePolicy().hasHeightForWidth());
        btnInsulin->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(btnInsulin, 0, 4, 1, 1);


        retranslateUi(HomePage);

        QMetaObject::connectSlotsByName(HomePage);
    } // setupUi

    void retranslateUi(QWidget *HomePage)
    {
        HomePage->setWindowTitle(QCoreApplication::translate("HomePage", "Form", nullptr));
        lblHomeTitle->setText(QCoreApplication::translate("HomePage", "Home", nullptr));
        btnProfiles->setText(QCoreApplication::translate("HomePage", "Profiles", nullptr));
        btnControlIQ->setText(QCoreApplication::translate("HomePage", "Control-IQ", nullptr));
        btnStatus->setText(QCoreApplication::translate("HomePage", "Status", nullptr));
        btnBolus->setText(QCoreApplication::translate("HomePage", "Bolus", nullptr));
        btnSettings->setText(QCoreApplication::translate("HomePage", "Settings", nullptr));
        btnPumpInfo->setText(QCoreApplication::translate("HomePage", "Pump Info", nullptr));
        btnGraph->setText(QCoreApplication::translate("HomePage", "Graph", nullptr));
        btnHistory->setText(QCoreApplication::translate("HomePage", "History", nullptr));
        btnLoadCartridge->setText(QCoreApplication::translate("HomePage", "Load Cartridge", nullptr));
        btnInsulin->setText(QCoreApplication::translate("HomePage", "Start/Stop Insulin", nullptr));
    } // retranslateUi

};

namespace Ui {
    class HomePage: public Ui_HomePage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HOMEPAGE_H
