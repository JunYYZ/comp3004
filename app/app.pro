# app/app.pro

QT       += core gui widgets
CONFIG   += c++17
TEMPLATE = app
TARGET   = tslimSimulator

SOURCES += \
    BolusPage.cpp \
    ControlIQPage.cpp \
    GraphPage.cpp \
    GraphWidget.cpp \
    HistoryLogPage.cpp \
    HomePage.cpp \
    LockPage.cpp \
    NumberKeypad.cpp \
    ProfileEditorPage.cpp \
    ProfileListPage.cpp \
    PumpInfoPage.cpp \
    SettingsPage.cpp \
    StatusPage.cpp \
    main.cpp \
    BolusCalculator.cpp \
    ErrorHandler.cpp \
    HistoryLog.cpp \
    Profile.cpp \
    ProfileManager.cpp \
    Pump.cpp \
    SimulationClock.cpp \
    CGM.cpp \
    ControlIQ.cpp \
    EventLogger.cpp \
    ChartModel.cpp \
    mainWindow.cpp

HEADERS += \
    BolusPage.h \
    ControlIQPage.h \
    GraphPage.h \
    GraphWidget.h \
    HistoryLogPage.h \
    HomePage.h \
    LockPage.h \
    NumberKeypad.h \
    Profile.h \
    ProfileEditorPage.h \
    ProfileListPage.h \
    PumpInfoPage.h \
    SettingsPage.h \
    StatusPage.h \
    BolusCalculator.h \
    ErrorHandler.h \
    HistoryLog.h \
    Profile.h \
    ProfileManager.h \
    Pump.h \
    SimulationClock.h \
    CGM.h \
    ControlIQ.h \
    EventLogger.h \
    ChartModel.h \
    mainWindow.h

FORMS += \
    BolusPage.ui \
    ControlIQPage.ui \
    GraphPage.ui \
    HistoryLogPage.ui \
    HomePage.ui \
    LockPage.ui \
    NumberKeypad.ui \
    ProfileEditorPage.ui \
    ProfileListPage.ui \
    PumpInfoPage.ui \
    SettingsPage.ui \
    StatusPage.ui \
    mainWindow.ui

# Deployment
qnx: target.path = /tmp/$$TARGET/bin
else: unix:!android: target.path = /opt/$$TARGET/bin
!isEmpty(target.path): INSTALLS += target
