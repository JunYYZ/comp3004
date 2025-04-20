/********************************************************************************
** Form generated from reading UI file 'mainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include "BolusPage.h"
#include "ControlIQPage.h"
#include "GraphPage.h"
#include "HistoryLogPage.h"
#include "HomePage.h"
#include "LockPage.h"
#include "ProfileEditorPage.h"
#include "ProfileListPage.h"
#include "PumpInfoPage.h"
#include "SettingsPage.h"
#include "StatusPage.h"

QT_BEGIN_NAMESPACE

class Ui_mainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QStackedWidget *stackedPages;
    LockPage *pageLock;
    HomePage *pageHome;
    StatusPage *pageStatus;
    BolusPage *pageBolus;
    ProfileListPage *pageProfileList;
    ProfileEditorPage *pageProfileEditor;
    HistoryLogPage *pageHistory;
    SettingsPage *pageSettings;
    GraphPage *pageGraph;
    PumpInfoPage *pagePumpInfo;
    ControlIQPage *pageControlIQ;
    QMenuBar *menubar;
    QMenu *menuLock;
    QMenu *menuHome;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *mainWindow)
    {
        if (mainWindow->objectName().isEmpty())
            mainWindow->setObjectName(QString::fromUtf8("mainWindow"));
        mainWindow->resize(791, 415);
        centralwidget = new QWidget(mainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setMinimumSize(QSize(791, 0));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        stackedPages = new QStackedWidget(centralwidget);
        stackedPages->setObjectName(QString::fromUtf8("stackedPages"));
        pageLock = new LockPage();
        pageLock->setObjectName(QString::fromUtf8("pageLock"));
        stackedPages->addWidget(pageLock);
        pageHome = new HomePage();
        pageHome->setObjectName(QString::fromUtf8("pageHome"));
        stackedPages->addWidget(pageHome);
        pageStatus = new StatusPage();
        pageStatus->setObjectName(QString::fromUtf8("pageStatus"));
        stackedPages->addWidget(pageStatus);
        pageBolus = new BolusPage();
        pageBolus->setObjectName(QString::fromUtf8("pageBolus"));
        stackedPages->addWidget(pageBolus);
        pageProfileList = new ProfileListPage();
        pageProfileList->setObjectName(QString::fromUtf8("pageProfileList"));
        stackedPages->addWidget(pageProfileList);
        pageProfileEditor = new ProfileEditorPage();
        pageProfileEditor->setObjectName(QString::fromUtf8("pageProfileEditor"));
        stackedPages->addWidget(pageProfileEditor);
        pageHistory = new HistoryLogPage();
        pageHistory->setObjectName(QString::fromUtf8("pageHistory"));
        stackedPages->addWidget(pageHistory);
        pageSettings = new SettingsPage();
        pageSettings->setObjectName(QString::fromUtf8("pageSettings"));
        stackedPages->addWidget(pageSettings);
        pageGraph = new GraphPage();
        pageGraph->setObjectName(QString::fromUtf8("pageGraph"));
        stackedPages->addWidget(pageGraph);
        pagePumpInfo = new PumpInfoPage();
        pagePumpInfo->setObjectName(QString::fromUtf8("pagePumpInfo"));
        stackedPages->addWidget(pagePumpInfo);
        pageControlIQ = new ControlIQPage();
        pageControlIQ->setObjectName(QString::fromUtf8("pageControlIQ"));
        stackedPages->addWidget(pageControlIQ);

        gridLayout->addWidget(stackedPages, 0, 0, 1, 1);

        mainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(mainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 791, 22));
        QFont font;
        font.setPointSize(10);
        menubar->setFont(font);
        menuLock = new QMenu(menubar);
        menuLock->setObjectName(QString::fromUtf8("menuLock"));
        menuHome = new QMenu(menubar);
        menuHome->setObjectName(QString::fromUtf8("menuHome"));
        mainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(mainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        statusbar->setFont(font);
        mainWindow->setStatusBar(statusbar);

        menubar->addAction(menuHome->menuAction());
        menubar->addAction(menuLock->menuAction());

        retranslateUi(mainWindow);

        QMetaObject::connectSlotsByName(mainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *mainWindow)
    {
        mainWindow->setWindowTitle(QCoreApplication::translate("mainWindow", "mainWindow", nullptr));
        menuLock->setTitle(QCoreApplication::translate("mainWindow", "Lock", nullptr));
        menuHome->setTitle(QCoreApplication::translate("mainWindow", "Home", nullptr));
    } // retranslateUi

};

namespace Ui {
    class mainWindow: public Ui_mainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
