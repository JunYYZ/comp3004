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
    if (!m_enabled) {
            emit predictionMade(std::numeric_limits<double>::quiet_NaN());
            return;
        }

    double prediction = predict30Min(glucose);
    emit predictionMade(prediction);
    qDebug() << "[ControlIQ] BG:" << glucose << "→30′ pred:" << prediction;

    // If predicted to go critically high, give a correction bolus:
    if (prediction > Pump::kCritHighBGThreshold) {
        qDebug() << "[ControlIQ] Pred > high threshold – auto‐bolus!";
        // use current glucose as “BG” so correctionFactor kicks in
        m_pump->deliverBolus(static_cast<int>(glucose), /*carbs=*/0);

    // If predicted to go critically low, suspend basal:
    } else if (prediction < Pump::kCritLowBGThreshold) {
        qDebug() << "[ControlIQ] Pred < low threshold – suspend basal!";
        m_pump->stopInsulin();
        emit stoppedForLowBG();
    // Otherwise, ensure basal is running:
    } else {
        // resume only if we were previously suspended
        m_pump->resumeInsulin();
    }
}

double ControlIQ::predict30Min(double currentBG)
{
    // super‐naïve: add a fixed upward drift of 0.5 mmol/L
    return currentBG + 0.5;
}
