# COMP3004 Group Project

Team Number: 29

Team Members: Nimish Bhatia, Michael Palummieri, Sajitha Polwatta, Nischal Shrestha, Junheng Zhang

Github Link: https://github.com/JunYYZ/comp3004/

# Video Link
https://youtu.be/uPL0Rct2Xhg

# Project Distribution

All:\
Use cases


**Nimish Bhatia:**\
Graph\
CGM\
UML State Machine for Insulin Delivery Subsystem\
UML State Machine for Pump Controller


**Michael Palummieri:**\
Control IQ\
Bolus Calaculator\
Manual Bolus\
Pump\
main\
GUI


**Sajitha Polwatta:**\
Profile\
profile crud/manager\
Video\
Normal Sequence Diagram


**Nischal Shrestha:**\
insulin delivery manager\
extended manual bolus\
Safety Sequence Diagram


**Junheng Zhang:**\
Warnings\
Logs\
Error handling\
Pump\
main\
tests\
UML Class diagram\
Use Case Diagram

# Compiling and running
To compile after unzipping,\
do:

cd app (go to app folder)\
qmake\
make

**OR** if that doesn't work

qmake app.pro\
make

To run:\
./tslimSimulator

or just double click the .exe

**IF QT CHARTS ERROR**
DO:\
sudo add-apt-repository universe\
sudo apt update\
sudo apt install libqt5charts5-dev\
sudo apt install qml-module-qtcharts

Then redo compile and running steps.

**ALTERNATIVELY**
launch Qt Creator by double clicking the app.pro file and configure the project to build and run using ide.


# Project organization:
```
.
└── comp3004-project/
    ├── readme.md                   -- this readme
    ├── app/
    │   ├── app.pro                 -- .pro makefile file
    │   ├── BGSimulator.cpp         -- headers, source, and qt ui files
    │   ├── BGSimulator.h           --  |
    │   ├── BolusCalculator.cpp     --  |
    │   ├── BolusCalculator.h       --  |
    │   ├── BolusPage.cpp           --  |
    │   ├── BolusPage.h             --  |
    │   ├── BolusPage.ui            --  |
    │   ├── ChartModel.cpp          --  |
    │   ├── ChartModel.h            --  |
    │   ├── ControlIQ.cpp           --  |
    │   ├── ControlIQ.h             --  |
    │   ├── ControlIQPage.cpp       --  |
    │   ├── ControlIQPage.h         --  |
    │   ├── ControlIQPage.ui        --  |
    │   ├── ErrorHandler.cpp        --  |
    │   ├── ErrorHandler.h          --  |
    │   ├── EventLogger.cpp         --  |
    │   ├── EventLogger.h           --  |
    │   ├── GraphPage.cpp           --  |
    │   ├── GraphPage.h             --  |
    │   ├── GraphPage.ui            --  |
    │   ├── GraphWidget.cpp         --  |
    │   ├── GraphWidget.h           --  |
    │   ├── HistoryLog.cpp          --  |
    │   ├── HistoryLog.h            --  |
    │   ├── HistoryLogPage.cpp      --  |
    │   ├── HistoryLogPage.h        --  |
    │   ├── HistoryLogPage.ui       --  |
    │   ├── HomePage.cpp            --  |
    │   ├── HomePage.h              --  |
    │   ├── HomePage.ui             --  |
    │   ├── LockPage.cpp            --  |
    │   ├── LockPage.h              --  |
    │   ├── LockPage.ui             --  |
    │   ├── main.cpp                --  |
    │   ├── mainWindow.cpp          --  |
    │   ├── mainWindow.h            --  |
    │   ├── mainWindow.ui           --  |
    │   ├── NumberKeypad.cpp        --  |
    │   ├── NumberKeypad.h          --  |
    │   ├── NumberKeypad.ui         --  |
    │   ├── Profile.cpp             --  |
    │   ├── Profile.h               --  |
    │   ├── ProfileEditorPage.cpp   --  |
    │   ├── ProfileEditorPage.h     --  |
    │   ├── ProfileEditorPage.ui    --  |
    │   ├── ProfileListPage.cpp     --  |
    │   ├── ProfileListPage.h       --  |
    │   ├── ProfileListPage.ui      --  |
    │   ├── ProfileManager.cpp      --  |
    │   ├── ProfileManager.h        --  |
    │   ├── Pump.cpp                --  |
    │   ├── Pump.h                  --  |
    │   ├── SettingsPage.cpp        --  |
    │   ├── SettingsPage.h          --  |
    │   ├── SettingsPage.ui         --  |
    │   ├── SimulationClock.cpp     --  |
    │   ├── SimulationClock.h       --  |
    │   ├── WarningDialog.cpp       --  |
    │   └── WarningDialog.h         --  v
    └── doc/
        ├── uml_diagrams/
        │   ├── Normal_Sequence_Diagram.png
        │   ├── safety_sequence_diagram.png
        │   ├── UML class.png
        │   ├── UML State Machine for Insulin Delivery Subsystem.png
        │   └── UML State Machine for Pump Controller.png
        ├── project-plan
        ├── project-doc             -- use cases, use case diagram, traceability matrix
        └── use case diagram.png    -- separate use case diagram in case the one in the doc breaks
```
