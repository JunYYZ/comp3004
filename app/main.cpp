#include <QApplication>
#include "mainWindow.h"
#include "SimulationClock.h"
#include "Pump.h"
#include "ControlIQ.h"
#include "EventLogger.h"
#include "BGSimulator.h"  // Include BGSimulator instead of CGM

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // The pump which delivers basal/bolus
    Pump* pump = new Pump(&app);

    // --- Instantiate core components ---
    // 1 real second = 5 simulated minutes
    SimulationClock* clock = new SimulationClock(1000, 5, /* parent: */ &app);
    clock->start();

    // BGSimulator emits a reading every 5 simulated minutes
    BGSimulator* bgSimulator = new BGSimulator(&app);  // Replace CGM with BGSimulator

    pump->setSimulationClock(clock);

    // Control‑IQ closed‑loop controller
    ControlIQ* ctrlIQ = new ControlIQ(pump, &app);

    // Logger for events
    EventLogger* logger = new EventLogger(&app);

    // --- Wire up the simulation ---
    QObject::connect(clock, &SimulationClock::tick,
                     bgSimulator, &BGSimulator::onTick);  // Connect clock to BGSimulator

    // When BGSimulator has a new reading, drive Control‑IQ and log
    QObject::connect(bgSimulator, &BGSimulator::newReading,
                     ctrlIQ, &ControlIQ::onNewReading);
    QObject::connect(bgSimulator, &BGSimulator::newReading,
                     [&](double glucose){
                         logger->log(
                             QString("BG reading: %1 mmol/L")
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

    // --- Start basal EventLogger* logger = new EventLogger(&app); and the sim clock ---
    pump->startInsulin();

    // --- Launch main window ---
    mainWindow w;
    w.show();

    return app.exec();
}
