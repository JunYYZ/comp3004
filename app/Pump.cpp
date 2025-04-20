#include "Pump.h"
#include "SimulationClock.h"
#include <cmath>

Pump::Pump(QObject *parent)
    : QObject(parent),
      m_battery(100),
      m_insulin(300),
      m_state(PumpState::IDLE),
      m_activeProfileIndex(-1),
      m_clock(nullptr),
      // Initialize simulated time to "now" or to some base; adjust as needed:
      m_simTime(QDateTime::currentDateTime())
{
    // Create ErrorHandler and forward its signals to pumpLog
    m_errorHandler = new ErrorHandler(this);
    connect(m_errorHandler, &ErrorHandler::warningRaised,
            this, [&](ErrorHandler::Warning w, QString msg){
                emit pumpLog(QString("WARNING [%1]: %2")
                             .arg(int(w)).arg(msg));
            });
    connect(m_errorHandler, &ErrorHandler::warningCleared,
            this, [&](ErrorHandler::Warning w){
                emit pumpLog(QString("WARNING CLEARED [%1]")
                             .arg(int(w)));
            });

    logEvent("Pump initialized");
    checkLevels();  // catch any startup warnings
}

void Pump::setSimulationClock(SimulationClock* clock)
{
    if (m_clock) {
        disconnect(m_clock, &SimulationClock::tick,
                   this,     &Pump::onSimulatedTimeAdvanced);
    }
    m_clock = clock;
    if (m_clock) {
        connect(m_clock, &SimulationClock::tick,
                this,     &Pump::onSimulatedTimeAdvanced);
    }
}

int Pump::batteryLevel() const
{
    return m_battery;
}

int Pump::insulinLevel() const
{
    return m_insulin;
}

PumpState Pump::state() const
{
    return m_state;
}

QVector<Profile> Pump::profiles() const
{
    return m_profiles;
}

void Pump::addProfile(const Profile &p)
{
    m_profiles.append(p);
    if (m_activeProfileIndex < 0)
        m_activeProfileIndex = 0;
    logEvent(QString("Profile added: %1").arg(p.name()));
}

bool Pump::selectActiveProfile(const QString &name)
{
    for (int i = 0; i < m_profiles.size(); ++i) {
        if (m_profiles[i].name() == name) {
            m_activeProfileIndex = i;
            logEvent(QString("Active profile set to '%1'").arg(name));
            emit pumpLog(QString("Profile: %1").arg(name));
            return true;
        }
    }
    emit pumpLog("Error: profile not found");
    return false;
}

double Pump::getInsulinOnBoard() const
{
    // TODO: implement real IOB calculation by scanning m_history
    return 0.0;
}

void Pump::startInsulin()
{
    if (m_state == PumpState::IDLE && m_activeProfileIndex >= 0) {
        m_state = PumpState::DELIVERING_BASAL;
        logEvent("Basal delivery started");
        emit pumpLog("Basal started");
    }
}

void Pump::stopInsulin()
{
    if (m_state == PumpState::DELIVERING_BASAL ||
        m_state == PumpState::DELIVERING_BOLUS) {
        m_state = PumpState::IDLE;
        logEvent("Insulin delivery stopped");
        emit pumpLog("Delivery stopped");
    }
}

void Pump::resumeInsulin()
{
    if (m_state == PumpState::IDLE && m_activeProfileIndex >= 0) {
        m_state = PumpState::DELIVERING_BASAL;
        logEvent("Basal resumed");
        emit pumpLog("Basal resumed");
    }
}

void Pump::deliverBolus(int currentBG, int carbs)
{
    if (m_activeProfileIndex < 0) {
        emit pumpLog("Error: no active profile");
        return;
    }

    // Pre-delivery safety check
    checkLevels();

    // Get the active profile
    Profile profile = m_profiles[m_activeProfileIndex];

    // Compute bolus components
    BolusCalculator calc(
        profile.carbRatio(),
        profile.correctionFactor(),
        getInsulinOnBoard()
    );
    double foodBolus = calc.foodBolus(static_cast<double>(carbs));
    double corrBolus = calc.correctionBolus(static_cast<double>(currentBG));
    double required  = foodBolus + corrBolus;
    double finalDose = calc.subtractIOB(required);

    // Cap to whatever insulin remains
    if (finalDose > m_insulin)
        finalDose = m_insulin;

    // Deliver the bolus
    m_insulin = static_cast<int>(std::round(m_insulin - finalDose));
    m_state   = PumpState::DELIVERING_BOLUS;

    // Log event
    logEvent(QString("Bolus delivered: %1 u (food:%2, corr:%3, IOB:%4)")
             .arg(finalDose)
             .arg(foodBolus)
             .arg(corrBolus)
             .arg(calc.insulinOnBoard()));
    emit pumpLog(QString("Delivered %1 units bolus").arg(finalDose));

    // Return to idle and re-check levels
    m_state = PumpState::IDLE;
    checkLevels();
}

void Pump::emergencyStop(const QString &reason)
{
    m_state = PumpState::EMERGENCY_STOP;
    logEvent(QString("Emergency Stop: %1").arg(reason));
    emit pumpLog(QString("Emergency Stop: %1").arg(reason));
}

void Pump::onSimulatedTimeAdvanced(int minutes)
{
    // Advance the internal simulated clock
    m_simTime = m_simTime.addSecs(minutes * 60);
    logEvent(QString("Sim time advanced by %1 minute(s)").arg(minutes));
}

void Pump::logEvent(const QString &desc)
{
    // Stamp with current simulated time
    m_history.append( HistoryLog(m_simTime, desc) );
    emit pumpLog(desc);
}

void Pump::checkLevels()
{
    // Battery warning
    if (m_battery <= kLowBatteryThreshold)
        m_errorHandler->raise(ErrorHandler::LowBattery, "Battery low");
    else
        m_errorHandler->clear(ErrorHandler::LowBattery);

    // Insulin warning
    if (m_insulin <= kLowInsulinThreshold)
        m_errorHandler->raise(ErrorHandler::LowInsulin, "Insulin low");
    else
        m_errorHandler->clear(ErrorHandler::LowInsulin);
}
