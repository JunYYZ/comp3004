// ControlIQ.cpp
#include "ControlIQ.h"

ControlIQ::ControlIQ(Pump* pump, QObject* parent)
    : QObject(parent), m_pump(pump)
{}

void ControlIQ::onNewReading(double glucose) {
    double pred = predict30Min(glucose);
    if (pred > Pump::kCritHighBGThreshold) {
        // auto-correction bolus
        m_pump->deliverBolus(static_cast<int>(glucose), 0);
    } else if (pred < Pump::kCritLowBGThreshold) {
        m_pump->stopInsulin();
    }
}

double ControlIQ::predict30Min(double currentBG) {
    // simplistic: assume drift
    return currentBG + 0.5;
}
