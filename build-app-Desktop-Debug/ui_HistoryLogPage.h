/********************************************************************************
** Form generated from reading UI file 'HistoryLogPage.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HISTORYLOGPAGE_H
#define UI_HISTORYLOGPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HistoryLogPage
{
public:
    QTableWidget *listHistory;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnClear;
    QPushButton *btnBack;

    void setupUi(QWidget *HistoryLogPage)
    {
        if (HistoryLogPage->objectName().isEmpty())
            HistoryLogPage->setObjectName(QString::fromUtf8("HistoryLogPage"));
        HistoryLogPage->resize(733, 334);
        listHistory = new QTableWidget(HistoryLogPage);
        if (listHistory->columnCount() < 2)
            listHistory->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        listHistory->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        listHistory->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        listHistory->setObjectName(QString::fromUtf8("listHistory"));
        listHistory->setGeometry(QRect(150, 30, 531, 251));
        listHistory->setColumnCount(2);
        listHistory->horizontalHeader()->setStretchLastSection(true);
        horizontalLayoutWidget = new QWidget(HistoryLogPage);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(370, 290, 281, 31));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        btnClear = new QPushButton(horizontalLayoutWidget);
        btnClear->setObjectName(QString::fromUtf8("btnClear"));

        horizontalLayout->addWidget(btnClear);

        btnBack = new QPushButton(horizontalLayoutWidget);
        btnBack->setObjectName(QString::fromUtf8("btnBack"));

        horizontalLayout->addWidget(btnBack);


        retranslateUi(HistoryLogPage);

        QMetaObject::connectSlotsByName(HistoryLogPage);
    } // setupUi

    void retranslateUi(QWidget *HistoryLogPage)
    {
        HistoryLogPage->setWindowTitle(QCoreApplication::translate("HistoryLogPage", "Form", nullptr));
        QTableWidgetItem *___qtablewidgetitem = listHistory->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("HistoryLogPage", "Time", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = listHistory->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("HistoryLogPage", "Event", nullptr));
        btnClear->setText(QCoreApplication::translate("HistoryLogPage", "Clear All", nullptr));
        btnBack->setText(QCoreApplication::translate("HistoryLogPage", "Back", nullptr));
    } // retranslateUi

};

namespace Ui {
    class HistoryLogPage: public Ui_HistoryLogPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HISTORYLOGPAGE_H
