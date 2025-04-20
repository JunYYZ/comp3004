/********************************************************************************
** Form generated from reading UI file 'LockPage.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOCKPAGE_H
#define UI_LOCKPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>
#include "NumberKeypad.h"

QT_BEGIN_NAMESPACE

class Ui_LockPage
{
public:
    QLabel *lblMessage;
    NumberKeypad *keypadPlaceholder;
    QLabel *lblPinDisplay;

    void setupUi(QWidget *LockPage)
    {
        if (LockPage->objectName().isEmpty())
            LockPage->setObjectName(QString::fromUtf8("LockPage"));
        LockPage->resize(773, 334);
        lblMessage = new QLabel(LockPage);
        lblMessage->setObjectName(QString::fromUtf8("lblMessage"));
        lblMessage->setGeometry(QRect(90, 20, 241, 81));
        QFont font;
        font.setPointSize(24);
        lblMessage->setFont(font);
        keypadPlaceholder = new NumberKeypad(LockPage);
        keypadPlaceholder->setObjectName(QString::fromUtf8("keypadPlaceholder"));
        keypadPlaceholder->setGeometry(QRect(420, 80, 193, 213));
        lblPinDisplay = new QLabel(LockPage);
        lblPinDisplay->setObjectName(QString::fromUtf8("lblPinDisplay"));
        lblPinDisplay->setGeometry(QRect(470, 30, 101, 31));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Liberation Sans"));
        font1.setPointSize(24);
        lblPinDisplay->setFont(font1);

        retranslateUi(LockPage);

        QMetaObject::connectSlotsByName(LockPage);
    } // setupUi

    void retranslateUi(QWidget *LockPage)
    {
        LockPage->setWindowTitle(QCoreApplication::translate("LockPage", "Form", nullptr));
        lblMessage->setText(QCoreApplication::translate("LockPage", "PUMP LOCKED", nullptr));
        lblPinDisplay->setText(QCoreApplication::translate("LockPage", "ERR", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LockPage: public Ui_LockPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOCKPAGE_H
