#include <QApplication>
#include <QDebug>

#include "mainWindow.h"
#include "SimulationClock.h"
#include "CGM.h"
#include "Pump.h"
#include "ControlIQ.h"
#include "EventLogger.h"

int main(int argc, char *argv[])
{
    // Use QApplication so we can show widgets
    QApplication app(argc, argv);

    // The pump which delivers basal/bolus
    Pump* pump = new Pump(&app);

    // --- Instantiate core components ---
    // 1 real second = 5 simulated minutes
    SimulationClock* clock = new SimulationClock(1000, 5, /* parent: */ &app);
    clock->start();
    // CGM emits a reading every 5 simulated minutes
    CGM* cgm = new CGM(5, /* parent: */ &app);

    pump->setSimulationClock(clock);


    // Control‑IQ closed‑loop controller
    ControlIQ* ctrlIQ = new ControlIQ(pump, &app);

    // Logger for events
    EventLogger* logger = new EventLogger(&app);

    // --- Wire up the simulation ---
    QObject::connect(clock, &SimulationClock::tick,
                     cgm,   &CGM::onTick);
//    QObject::connect(clock, &SimulationClock::tick,
//                     pump,  &Pump::checkLevels);

    // When CGM has a new reading, drive Control‑IQ and log
    QObject::connect(cgm, &CGM::newReading,
                     ctrlIQ, &ControlIQ::onNewReading);
    QObject::connect(cgm, &CGM::newReading,
                     [&](double glucose){
                         logger->log(
                             QString("CGM reading: %1 mmol/L")
                                 .arg(glucose, 0, 'f', 1)
                         );
                     });

    // Pump emits pumpLog() for any event — log + print
    QObject::connect(pump, &Pump::pumpLog,
                     [&](const QString &msg){
                         logger->log(msg);
                         qDebug() << msg;
                     });

    QObject::connect(pump,   &Pump::pumpLog,
                     logger, &EventLogger::log);

    // --- Start basal EventLogger*  logger = new EventLogger(&app); and the sim clock ---
    pump->startInsulin();

    // --- Launch main window ---
    mainWindow w;
    w.show();

    return app.exec();
}