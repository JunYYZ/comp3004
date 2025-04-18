// ControlIQ.h
#ifndef CONTROLIQ_H
#define CONTROLIQ_H

#include <QObject>
#include "Pump.h"

/**
 * @brief ControlIQ algorithm adjusts insulin based on predicted BG.
 */
class ControlIQ : public QObject {
    Q_OBJECT
public:
    ControlIQ(Pump* pump, QObject* parent = nullptr);

public slots:
    /** Connect to CGM::newReading */
    void onNewReading(double glucose);

private:
    Pump* m_pump;
    double predict30Min(double currentBG);
};
#endif // CONTROLIQ_H
