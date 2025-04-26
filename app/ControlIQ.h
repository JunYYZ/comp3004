// ControlIQ.h
#ifndef CONTROLIQ_H
#define CONTROLIQ_H

#include <QObject>
#include "Pump.h"

/**
 * @brief ControlIQ algorithm adjusts insulin based on predicted BG.
 */
// ControlIQ.h
class ControlIQ : public QObject {
    Q_OBJECT
public:
    explicit ControlIQ(Pump* pump, QObject* parent=nullptr);

    bool isEnabled() const;
public slots:
    void setEnabled(bool on);
    void onNewReading(double glucose);

signals:
    void enabledChanged(bool enabled);
    void predictionMade(double prediction);
    void stoppedForLowBG();
    void insulinLevelUpdated(int newLevel);

private:
    double predict30Min(double currentBG);
    Pump*  m_pump;
    bool   m_enabled = false;
};

#endif // CONTROLIQ_H
