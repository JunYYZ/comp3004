// Pump.cpp
#include "Pump.h"
#include "SimulationClock.h"

#include <cmath>
#include <algorithm>
#include <QDebug>

// Update IOB with insulin reservoir, not IOB
inline void Pump::maybeEmitIOB()
{
    double now = m_insulin;  // Use the insulin level directly for IOB
    if (std::fabs(now - m_cachedIOB) >= 0.01) {  // 1 × 0.01 U step
        m_cachedIOB = now;
        emit iobChanged(now);
    }
}

// Constructor & basic plumbing (Initialize m_insulin, m_insulinOnBoard)
Pump::Pump(QObject *parent)
    : QObject(parent),
      m_battery(100),
      m_insulin(300),  // Insulin level in reservoir
      m_totalSimulatedMinutes(0),
      m_state(PumpState::IDLE),
      m_activeProfileIndex(-1),
      m_clock(nullptr),
      m_simTime(QDateTime::currentDateTime()),
      m_insulinOnBoard(0.0),  // Initialize insulin on board to 0.0
      m_insulinActionDuration(240.0)  // Duration for insulin action (e.g., 4 hours)
{
    m_errorHandler = new ErrorHandler(this);
    connect(m_errorHandler, &ErrorHandler::warningRaised,
            this, &Pump::warningRaised);
    connect(m_errorHandler, &ErrorHandler::warningCleared,
            this, &Pump::warningCleared);

    logEvent("Pump initialized");
    checkLevels();  // Check for any warnings
}

// Simulation clock hookup for IOB and insulin delivery timing
void Pump::setSimulationClock(SimulationClock* clk)
{
    if (m_clock) {
        disconnect(m_clock, &SimulationClock::tick,
                   this, &Pump::onSimulatedTimeAdvanced);
    }
    m_clock = clk;
    if (m_clock) {
        connect(m_clock, &SimulationClock::tick,
                this, &Pump::onSimulatedTimeAdvanced);
    }
}

// IOB helpers (use m_insulin, not m_insulinOnBoard)
double Pump::currentIOB() const
{
    return m_insulin;  // Directly return the insulin left in the reservoir
}

void Pump::ageAndPruneIOB(int mins)
{
    // Decay the insulin in the system over time based on the duration
    if (m_insulinOnBoard > 0.0) {
        double decay = (mins / m_insulinActionDuration) * m_insulinOnBoard;
        m_insulinOnBoard = std::max(0.0, m_insulinOnBoard - decay);
    }
    maybeEmitIOB();
}

// Basal and bolus logic using m_insulin directly
void Pump::startInsulin()
{
    if (m_state != PumpState::IDLE || m_activeProfileIndex < 0) return;
    m_state = PumpState::DELIVERING_BASAL;
    logEvent("Basal delivery started");
    emit pumpLog("Basal started");
}

void Pump::stopInsulin()
{
    if (m_state == PumpState::DELIVERING_BASAL || m_state == PumpState::DELIVERING_BOLUS) {
        m_state = PumpState::IDLE;
        logEvent("Insulin delivery stopped");
        emit basalRateChanged(0.0);
        emit pumpLog("Delivery stopped");
    }
}

void Pump::resumeInsulin()
{
    if (m_state == PumpState::IDLE && m_activeProfileIndex >= 0) {
        m_state = PumpState::DELIVERING_BASAL;
        logEvent("Basal resumed");
        emit basalRateChanged(m_profiles[m_activeProfileIndex].basalRate());
        emit pumpLog("Basal resumed");
    }
}

// Deliver bolus using insulin directly and updating IOB
void Pump::deliverBolus(int currentBG, int carbs)
{
    if (m_activeProfileIndex < 0) {
        emit pumpLog("Error: no active profile");
        return;
    }
    checkLevels();

    const Profile& profile = m_profiles[m_activeProfileIndex];
    BolusCalculator calc(profile.carbRatio(), profile.correctionFactor(), m_insulinOnBoard);

    double foodBolus = calc.foodBolus(double(carbs));
    double corrBolus = calc.correctionBolus(double(currentBG));
    double required  = foodBolus + corrBolus;
    double finalDose = calc.subtractIOB(required);

    const double maxSafeDose = 15.0;
    if (finalDose > maxSafeDose) finalDose = maxSafeDose;
    if (finalDose > m_insulin)   finalDose = m_insulin;
    if (finalDose <= 0.0)        return;

    // Update insulin directly (deduct from reservoir)
    m_insulin -= int(std::round(finalDose));
    emit reservoirChanged(m_insulin);

    // Update insulin on board and emit IOB
    m_insulinOnBoard += finalDose; // Add bolus to IOB
    maybeEmitIOB();

    logEvent(QString("Bolus %1 U (food:%2  corr:%3  IOB:%4)")
             .arg(finalDose).arg(foodBolus).arg(corrBolus).arg(m_insulinOnBoard));

    emit pumpLog(QString("Delivered %1 U bolus").arg(finalDose));
    emit bolusDelivered(finalDose, carbs);
}

// Handle IOB updates based on time (via simulation clock)
void Pump::onSimulatedTimeAdvanced(int minutes)
{
    m_simTime = m_simTime.addSecs(minutes * 60);
    m_totalSimulatedMinutes += minutes;

    // Decay insulin on board over time based on action duration
    if (m_insulinOnBoard > 0.0) {
        double decay = (minutes / m_insulinActionDuration) * m_insulinOnBoard;
        m_insulinOnBoard = std::max(0.0, m_insulinOnBoard - decay);
    }

    // Battery and insulin level checks
    int chunks = m_totalSimulatedMinutes / 25;
    int newBattery = std::max(0, 100 - chunks * 5);
    if (newBattery != m_battery) {
        m_battery = newBattery;
        emit batteryLevelChanged(m_battery);
    }

    // Deliver basal insulin if in basal mode
    if (m_state == PumpState::DELIVERING_BASAL && m_activeProfileIndex >= 0) {
        const Profile &profile = m_profiles[m_activeProfileIndex];
        double ratePerHour = profile.basalRate(); // U/hr
        double unitsThisTick = ratePerHour * (minutes / 60.0);
        int deliveredUnits = int(std::round(unitsThisTick));

        if (deliveredUnits > 0) {
            m_insulin = std::max(0, m_insulin - deliveredUnits);
            logEvent(QString("Basal delivered: %1 U over %2 min")
                     .arg(deliveredUnits).arg(minutes));
        }
    }

    // Emit insulin on board if changed
    maybeEmitIOB();
    checkLevels();
}

// Level checks for insulin and battery
void Pump::checkLevels()
{
    if (m_battery <= kLowBatteryThreshold)
        m_errorHandler->raise(ErrorHandler::LowBattery, "Battery low");
    else
        m_errorHandler->clear(ErrorHandler::LowBattery);

    if (m_insulin <= kLowInsulinThreshold)
        m_errorHandler->raise(ErrorHandler::LowInsulin, "Insulin low");
    else
        m_errorHandler->clear(ErrorHandler::LowInsulin);
}

// Charge battery
void Pump::chargeBattery()
{
    int old = m_battery;
    m_battery = std::min(m_battery + 25, 100);
    if (m_battery != old) {
        logEvent(QString("Battery charged to %1 %").arg(m_battery));
        emit batteryLevelChanged(m_battery);
        m_totalSimulatedMinutes = 0;  // reset drain
        m_errorHandler->clear(ErrorHandler::LowBattery);
    }
}

// Refill insulin reservoir
void Pump::fillInsulin()
{
    m_insulin = 300;
    emit insulinLevelChanged(m_insulin);
    logEvent("Cartridge refilled to 300 U");
    emit pumpLog("Insulin refilled");
    m_errorHandler->clear(ErrorHandler::LowInsulin);
}

bool Pump::selectActiveProfile(const QString &name) {
    // Iterate through profiles and set the active profile
    for (int i = 0; i < m_profiles.size(); ++i) {
        if (m_profiles[i].name() == name) {
            m_activeProfileIndex = i;
            emit pumpLog(QString("Profile: %1").arg(name));
            return true;
        }
    }
    emit pumpLog("Error: profile not found");
    return false;
}

int Pump::insulinLevel() const {
    return m_insulin;  // Assuming m_insulin holds the current insulin level
}

void Pump::addProfile(const Profile &p) {
    m_profiles.append(p);
}

int Pump::batteryLevel() const {
    return m_battery;
}

void Pump::logEvent(const QString &desc) {
    // Assuming you want to log events into a history or console
    m_history.append(HistoryLog(m_simTime, desc));  // Store in history
    emit pumpLog(desc);  // Emit to GUI or external logging
}

void Pump::deliverExtendedBolus(double totalUnits, int pctNow, int durationMin) {
    int currentBG = 0;  // Assuming you want to use current BG in the logic

    // First, deliver the immediate portion (like a regular bolus)
    deliverBolus(currentBG, 0);  // Call existing deliverBolus function for the "now" part

    // Now add the 'now' portion to IOB (Insulin on Board)
    double nowU = totalUnits * pctNow / 100.0;
    m_iob.append({ nowU, 0 });  // Add the now chunk to the IOB list
    maybeEmitIOB();  // Emit updated IOB

    logEvent(QString("[Extended Bolus] Delivered %1 U immediately").arg(nowU));
}

PumpState Pump::state() const {
    return m_state;  // assuming m_state is the state variable in the class
}
