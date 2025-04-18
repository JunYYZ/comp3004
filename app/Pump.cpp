#include "Pump.h"
#include <cmath>

Pump::Pump(QObject *parent)
    : QObject(parent),
      m_battery(100),
      m_insulin(300),
      m_state(PumpState::IDLE),
      m_activeProfileIndex(-1)
{
    // Instantiate the ErrorHandler and hook up its signals to our pumpLog
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
    checkLevels();  // ensure no warnings at startup
}

int Pump::batteryLevel() const { return m_battery; }
int Pump::insulinLevel() const { return m_insulin; }
PumpState Pump::state() const  { return m_state; }

void Pump::addProfile(const Profile &p)
{
    m_profiles.append(p);
    if (m_activeProfileIndex < 0)
        m_activeProfileIndex = 0;
    logEvent(QString("Profile added: %1").arg(p.name()));
}

QVector<Profile> Pump::profiles() const
{
    return m_profiles;
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

void Pump::startInsulin()
{
    if (m_state == PumpState::IDLE) {
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
    if (m_state == PumpState::IDLE &&
        m_activeProfileIndex >= 0) {
        m_state = PumpState::DELIVERING_BASAL;
        logEvent("Basal resumed");
        emit pumpLog("Basal resumed");
    }
}

double Pump::getInsulinOnBoard() const
{
    // TODO: Aggregate recent bolus history to compute active IOB.
    return 0.0;
}

void Pump::deliverBolus(int currentBG, int carbs)
{
    if (m_activeProfileIndex < 0) {
        emit pumpLog("Error: no active profile");
        return;
    }

    // 1) pre‐delivery check
    checkLevels();

    // 2) Fetch profile parameters
    Profile profile = m_profiles[m_activeProfileIndex];

    // Construct BolusCalculator in correct order: (carbRatio, correctionFactor, IOB)
    BolusCalculator calc(
        profile.carbRatio(),
        profile.correctionFactor(),
        getInsulinOnBoard()
    );

    // 3) Compute each piece
    double foodBolus = calc.foodBolus(static_cast<double>(carbs));
    double corrBolus = calc.correctionBolus(static_cast<double>(currentBG));
    double required  = foodBolus + corrBolus;
    double finalDose = calc.subtractIOB(required);

    // 4) Cap if more insulin than remains
    if (finalDose > m_insulin)
        finalDose = m_insulin;

    // 5) Deliver
    m_insulin = static_cast<int>(std::round(m_insulin - finalDose));
    m_state   = PumpState::DELIVERING_BOLUS;

    // 6) Log and notify
    logEvent(QString("Bolus delivered: %1u (food:%2, corr:%3, IOB:%4)")
             .arg(finalDose)
             .arg(foodBolus)
             .arg(corrBolus)
             .arg(calc.insulinOnBoard()));
    emit pumpLog(QString("Delivered %1 units bolus").arg(finalDose));

    // 7) Return to idle and re‐check warnings
    m_state = PumpState::IDLE;
    checkLevels();
}

void Pump::emergencyStop(const QString &reason)
{
    m_state = PumpState::EMERGENCY_STOP;
    logEvent(QString("Emergency Stop: %1").arg(reason));
    emit pumpLog(QString("Emergency Stop: %1").arg(reason));
}

void Pump::logEvent(const QString &desc)
{
    m_history.append(HistoryLog(desc));
}

void Pump::checkLevels()
{
    // Low battery?
    if (m_battery <= kLowBatteryThreshold)
        m_errorHandler->raise(ErrorHandler::LowBattery, "Battery low");
    else
        m_errorHandler->clear(ErrorHandler::LowBattery);

    // Low insulin?
    if (m_insulin <= kLowInsulinThreshold)
        m_errorHandler->raise(ErrorHandler::LowInsulin, "Insulin low");
    else
        m_errorHandler->clear(ErrorHandler::LowInsulin);
}
