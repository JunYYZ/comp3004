// CGM.h
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

signals:
    /** Emitted when a new glucose reading is available */
    void newReading(double glucose);

public slots:
    /** Call when simulation clock ticks */
    void onTick(int simMinute);

private:
    int m_interval;
    double generateValue();
};
#endif // CGM_H
