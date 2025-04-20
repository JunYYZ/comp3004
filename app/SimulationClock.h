#ifndef SIMULATIONCLOCK_H
#define SIMULATIONCLOCK_H

#include <QObject>
#include <QTimer>

/// Emits a `tick(int)` signal every real‐ms interval, telling you
/// “this many simulated minutes have passed.”
class SimulationClock : public QObject {
    Q_OBJECT
public:
    /// @param realIntervalMs    how many real ms between ticks
    /// @param minsPerTick       how many simulated minutes each tick represents
    /// @param parent            QObject parent
    explicit SimulationClock(int realIntervalMs,
                             int minsPerTick,
                             QObject* parent = nullptr);

    /// Start the repeating timer
    void start();

    /// Total simulated minutes elapsed since start()
    int elapsedMinutes() const { return m_elapsed; }

signals:
    /// Emitted on every timeout:
    ///   int = how many simulated minutes since the *last* tick
    void tick(int simulatedMinutes);

private slots:
    void onTimeout();

private:
    QTimer  m_timer;
    int     m_minsPerTick;
    int     m_elapsed = 0;
};

#endif // SIMULATIONCLOCK_H
