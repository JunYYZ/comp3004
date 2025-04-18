// SimulationClock.h
#ifndef SIMULATIONCLOCK_H
#define SIMULATIONCLOCK_H

#include <QObject>
#include <QTimer>

/**
 * @brief SimulationClock maps real time to simulated time and emits ticks.
 */
class SimulationClock : public QObject {
    Q_OBJECT
public:
    /**
     * @param realIntervalMs  real interval in ms (e.g., 1000ms)
     * @param simMinutesPerRealInterval  how many simulated minutes per real tick (e.g., 5)
     */
    SimulationClock(int realIntervalMs, int simMinutesPerRealInterval, QObject* parent = nullptr);
    void start();
    void stop();
    int simulatedMinutes() const;

signals:
    /** Emitted on each simulation tick */
    void tick(int simMinute);

private slots:
    void onTimeout();

private:
    QTimer m_timer;
    int m_simMinutesPerTick;
    int m_totalSimMinutes;
};
#endif // SIMULATIONCLOCK_H
