#include "ControlIQ.h"
#include "Pump.h"

#include <QDebug>

ControlIQ::ControlIQ(Pump* pump, QObject* parent)
    : QObject(parent)
    , m_pump(pump)
{
    Q_ASSERT(pump);
    emit enabledChanged(m_enabled);
}

void ControlIQ::setEnabled(bool on)
{
    if (m_enabled == on) return;  // If already in the correct state, no need to toggle again
    m_enabled = on;

    if (m_enabled) {
        // Enable ControlIQ logic (e.g., start insulin delivery, prediction)
        qDebug() << "[ControlIQ] Enabled!";
    } else {
        // Disable ControlIQ logic (e.g., stop insulin delivery, prediction)
        qDebug() << "[ControlIQ] Disabled!";
    }

    emit enabledChanged(m_enabled);  // Notify that the state has changed
}



bool ControlIQ::isEnabled() const
{
    return m_enabled;
}

void ControlIQ::onNewReading(double glucose)
{
    // Check if ControlIQ is enabled
    if (!m_enabled) {
        emit predictionMade(std::numeric_limits<double>::quiet_NaN());
        return;
    }

    double prediction = predict30Min(glucose);
    emit predictionMade(prediction);

    // Logic to handle high/low BGs and basal delivery
    if (prediction > Pump::kCritHighBGThreshold) {
        m_pump->deliverBolus(static_cast<int>(glucose), 0);  // Handle bolus delivery
    } else if (prediction < Pump::kCritLowBGThreshold) {
        m_pump->stopInsulin();  // Stop basal if BG is low
        emit stoppedForLowBG();
    } else {
        m_pump->resumeInsulin();  // Resume basal delivery if BG is normal
    }

    // Decrease insulin in the status bar as basal insulin is being delivered
    if (m_pump->state() == PumpState::DELIVERING_BASAL) {
        emit insulinLevelUpdated(m_pump->insulinLevel());  // Emit updated insulin level
    }
}


double ControlIQ::predict30Min(double currentBG)
{
    // super‐naïve: add a fixed upward drift of 0.5 mmol/L
    return currentBG + 0.5;
}
