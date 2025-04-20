/********************************************************************************
** Form generated from reading UI file 'BolusPage.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BOLUSPAGE_H
#define UI_BOLUSPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BolusPage
{
public:
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QLabel *lblTitle;
    QGridLayout *gridLayout;
    QLabel *lblCurrentBG;
    QDoubleSpinBox *sbCurrentBG;
    QLabel *lblCarbs;
    QDoubleSpinBox *sbCarbs;
    QPushButton *btnDeliver;
    QLabel *lblSuggested;
    QPushButton *btnCancel;

    void setupUi(QWidget *BolusPage)
    {
        if (BolusPage->objectName().isEmpty())
            BolusPage->setObjectName(QString::fromUtf8("BolusPage"));
        BolusPage->resize(773, 334);
        widget = new QWidget(BolusPage);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(0, 0, 771, 331));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        lblTitle = new QLabel(widget);
        lblTitle->setObjectName(QString::fromUtf8("lblTitle"));
        QFont font;
        font.setPointSize(18);
        font.setBold(true);
        font.setWeight(75);
        lblTitle->setFont(font);

        verticalLayout->addWidget(lblTitle);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        lblCurrentBG = new QLabel(widget);
        lblCurrentBG->setObjectName(QString::fromUtf8("lblCurrentBG"));

        gridLayout->addWidget(lblCurrentBG, 0, 0, 1, 1);

        sbCurrentBG = new QDoubleSpinBox(widget);
        sbCurrentBG->setObjectName(QString::fromUtf8("sbCurrentBG"));
        sbCurrentBG->setDecimals(1);
        sbCurrentBG->setMinimum(1.000000000000000);
        sbCurrentBG->setMaximum(25.000000000000000);
        sbCurrentBG->setSingleStep(0.100000000000000);

        gridLayout->addWidget(sbCurrentBG, 0, 1, 1, 1);

        lblCarbs = new QLabel(widget);
        lblCarbs->setObjectName(QString::fromUtf8("lblCarbs"));

        gridLayout->addWidget(lblCarbs, 1, 0, 1, 1);

        sbCarbs = new QDoubleSpinBox(widget);
        sbCarbs->setObjectName(QString::fromUtf8("sbCarbs"));
        sbCarbs->setDecimals(1);
        sbCarbs->setMaximum(200.000000000000000);

        gridLayout->addWidget(sbCarbs, 1, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);

        btnDeliver = new QPushButton(widget);
        btnDeliver->setObjectName(QString::fromUtf8("btnDeliver"));

        verticalLayout->addWidget(btnDeliver);

        lblSuggested = new QLabel(widget);
        lblSuggested->setObjectName(QString::fromUtf8("lblSuggested"));
        QFont font1;
        font1.setPointSize(14);
        font1.setItalic(true);
        lblSuggested->setFont(font1);

        verticalLayout->addWidget(lblSuggested);

        btnCancel = new QPushButton(widget);
        btnCancel->setObjectName(QString::fromUtf8("btnCancel"));

        verticalLayout->addWidget(btnCancel);


        retranslateUi(BolusPage);

        QMetaObject::connectSlotsByName(BolusPage);
    } // setupUi

    void retranslateUi(QWidget *BolusPage)
    {
        BolusPage->setWindowTitle(QCoreApplication::translate("BolusPage", "Form", nullptr));
        lblTitle->setText(QCoreApplication::translate("BolusPage", "Manual Bolus", nullptr));
        lblCurrentBG->setText(QCoreApplication::translate("BolusPage", "Current BG (mmol/L):", nullptr));
        lblCarbs->setText(QCoreApplication::translate("BolusPage", "Carbs (g):", nullptr));
        btnDeliver->setText(QCoreApplication::translate("BolusPage", "Deliver", nullptr));
        lblSuggested->setText(QString());
        btnCancel->setText(QCoreApplication::translate("BolusPage", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BolusPage: public Ui_BolusPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BOLUSPAGE_H
