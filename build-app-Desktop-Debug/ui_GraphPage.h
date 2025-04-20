/********************************************************************************
** Form generated from reading UI file 'GraphPage.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GRAPHPAGE_H
#define UI_GRAPHPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "GraphWidget.h"

QT_BEGIN_NAMESPACE

class Ui_GraphPage
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QComboBox *comboRange;
    GraphWidget *graphWidget;
    QPushButton *btnBack;

    void setupUi(QWidget *GraphPage)
    {
        if (GraphPage->objectName().isEmpty())
            GraphPage->setObjectName(QString::fromUtf8("GraphPage"));
        GraphPage->resize(733, 334);
        verticalLayoutWidget = new QWidget(GraphPage);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(119, 9, 581, 311));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        comboRange = new QComboBox(verticalLayoutWidget);
        comboRange->addItem(QString());
        comboRange->addItem(QString());
        comboRange->addItem(QString());
        comboRange->setObjectName(QString::fromUtf8("comboRange"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(comboRange->sizePolicy().hasHeightForWidth());
        comboRange->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(comboRange);

        graphWidget = new GraphWidget(verticalLayoutWidget);
        graphWidget->setObjectName(QString::fromUtf8("graphWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(graphWidget->sizePolicy().hasHeightForWidth());
        graphWidget->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(graphWidget);

        btnBack = new QPushButton(verticalLayoutWidget);
        btnBack->setObjectName(QString::fromUtf8("btnBack"));

        verticalLayout->addWidget(btnBack);

        verticalLayout->setStretch(1, 1);

        retranslateUi(GraphPage);

        QMetaObject::connectSlotsByName(GraphPage);
    } // setupUi

    void retranslateUi(QWidget *GraphPage)
    {
        GraphPage->setWindowTitle(QCoreApplication::translate("GraphPage", "Form", nullptr));
        comboRange->setItemText(0, QCoreApplication::translate("GraphPage", "1 hr", nullptr));
        comboRange->setItemText(1, QCoreApplication::translate("GraphPage", "3 hr", nullptr));
        comboRange->setItemText(2, QCoreApplication::translate("GraphPage", "6 hr", nullptr));

        btnBack->setText(QCoreApplication::translate("GraphPage", "Back", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GraphPage: public Ui_GraphPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GRAPHPAGE_H
