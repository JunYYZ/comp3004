#ifndef CGM_H
#define CGM_H

#include <QObject>

/**
 * @brief CGM simulates Continuous Glucose Monitoring readings.
 */
class CGM : public QObject {
    Q_OBJECT
public:
    /**
     * @param intervalSimMinutes  how often to emit (simulated) minutes
     */
    CGM(int intervalSimMinutes, QObject* parent = nullptr);

    /// Returns the most recent BG value (mmol/L)
    double latestBG() const;

signals:
    /// Emitted when a new glucose reading is available
    void newReading(double glucose);

public slots:
    /// Call this every time the simulation clock ticks
    void onTick(int simMinute);
    void onBolusEffect(double units);

private:
    int m_interval;     // how often to emit in sim minutes
    double m_lastBG;    // latest glucose value (mmol/L)
    double generateValue();
};

#endif // CGM_H
