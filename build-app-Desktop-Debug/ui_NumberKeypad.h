/********************************************************************************
** Form generated from reading UI file 'NumberKeypad.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NUMBERKEYPAD_H
#define UI_NUMBERKEYPAD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NumberKeypad
{
public:
    QGridLayout *gridLayout;
    QPushButton *btn1;
    QPushButton *btn2;
    QPushButton *btn3;
    QPushButton *btn4;
    QPushButton *btn5;
    QPushButton *btn6;
    QPushButton *btn7;
    QPushButton *btn8;
    QPushButton *btn9;
    QPushButton *btnDEL;
    QPushButton *btn0;
    QPushButton *btnOK;

    void setupUi(QWidget *NumberKeypad)
    {
        if (NumberKeypad->objectName().isEmpty())
            NumberKeypad->setObjectName(QString::fromUtf8("NumberKeypad"));
        NumberKeypad->resize(192, 213);
        gridLayout = new QGridLayout(NumberKeypad);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        btn1 = new QPushButton(NumberKeypad);
        btn1->setObjectName(QString::fromUtf8("btn1"));

        gridLayout->addWidget(btn1, 0, 0, 1, 1);

        btn2 = new QPushButton(NumberKeypad);
        btn2->setObjectName(QString::fromUtf8("btn2"));

        gridLayout->addWidget(btn2, 0, 1, 1, 1);

        btn3 = new QPushButton(NumberKeypad);
        btn3->setObjectName(QString::fromUtf8("btn3"));

        gridLayout->addWidget(btn3, 0, 2, 1, 1);

        btn4 = new QPushButton(NumberKeypad);
        btn4->setObjectName(QString::fromUtf8("btn4"));

        gridLayout->addWidget(btn4, 1, 0, 1, 1);

        btn5 = new QPushButton(NumberKeypad);
        btn5->setObjectName(QString::fromUtf8("btn5"));

        gridLayout->addWidget(btn5, 1, 1, 1, 1);

        btn6 = new QPushButton(NumberKeypad);
        btn6->setObjectName(QString::fromUtf8("btn6"));

        gridLayout->addWidget(btn6, 1, 2, 1, 1);

        btn7 = new QPushButton(NumberKeypad);
        btn7->setObjectName(QString::fromUtf8("btn7"));

        gridLayout->addWidget(btn7, 2, 0, 1, 1);

        btn8 = new QPushButton(NumberKeypad);
        btn8->setObjectName(QString::fromUtf8("btn8"));

        gridLayout->addWidget(btn8, 2, 1, 1, 1);

        btn9 = new QPushButton(NumberKeypad);
        btn9->setObjectName(QString::fromUtf8("btn9"));

        gridLayout->addWidget(btn9, 2, 2, 1, 1);

        btnDEL = new QPushButton(NumberKeypad);
        btnDEL->setObjectName(QString::fromUtf8("btnDEL"));

        gridLayout->addWidget(btnDEL, 3, 0, 1, 1);

        btn0 = new QPushButton(NumberKeypad);
        btn0->setObjectName(QString::fromUtf8("btn0"));

        gridLayout->addWidget(btn0, 3, 1, 1, 1);

        btnOK = new QPushButton(NumberKeypad);
        btnOK->setObjectName(QString::fromUtf8("btnOK"));

        gridLayout->addWidget(btnOK, 3, 2, 1, 1);


        retranslateUi(NumberKeypad);

        QMetaObject::connectSlotsByName(NumberKeypad);
    } // setupUi

    void retranslateUi(QWidget *NumberKeypad)
    {
        NumberKeypad->setWindowTitle(QCoreApplication::translate("NumberKeypad", "Form", nullptr));
        btn1->setText(QCoreApplication::translate("NumberKeypad", "1", nullptr));
        btn2->setText(QCoreApplication::translate("NumberKeypad", "2", nullptr));
        btn3->setText(QCoreApplication::translate("NumberKeypad", "3", nullptr));
        btn4->setText(QCoreApplication::translate("NumberKeypad", "4", nullptr));
        btn5->setText(QCoreApplication::translate("NumberKeypad", "5", nullptr));
        btn6->setText(QCoreApplication::translate("NumberKeypad", "6", nullptr));
        btn7->setText(QCoreApplication::translate("NumberKeypad", "7", nullptr));
        btn8->setText(QCoreApplication::translate("NumberKeypad", "8", nullptr));
        btn9->setText(QCoreApplication::translate("NumberKeypad", "9", nullptr));
        btnDEL->setText(QCoreApplication::translate("NumberKeypad", "DEL", nullptr));
        btn0->setText(QCoreApplication::translate("NumberKeypad", "0", nullptr));
        btnOK->setText(QCoreApplication::translate("NumberKeypad", "OK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NumberKeypad: public Ui_NumberKeypad {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NUMBERKEYPAD_H
