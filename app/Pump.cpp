#include "Pump.h"
#include "SimulationClock.h"

#include <cmath>
#include <algorithm>
#include <QDebug>

Pump::Pump(QObject *parent)
    : QObject(parent),
      m_battery(100),
      m_insulin(300),
      m_totalSimulatedMinutes(0),
      m_state(PumpState::IDLE),
      m_activeProfileIndex(-1),
      m_clock(nullptr),
      m_simTime(QDateTime::currentDateTime()),
      m_insulinOnBoard(0.0),
      m_insulinActionDuration(240.0) // minutes (e.g. 4 h)
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

    connect(m_errorHandler, &ErrorHandler::warningRaised,
            this, &Pump::warningRaised);
    connect(m_errorHandler, &ErrorHandler::warningCleared,
            this, &Pump::warningCleared);

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
    return m_insulinOnBoard;
}

void Pump::startInsulin()
{
    if (m_state == PumpState::IDLE && m_activeProfileIndex >= 0) {
        m_state = PumpState::DELIVERING_BASAL;
        logEvent("Basal delivery started");
        emit basalRateChanged(m_profiles[m_activeProfileIndex].basalRate());
        emit pumpLog("Basal started");
    }
}

void Pump::stopInsulin()
{
    if (m_state == PumpState::DELIVERING_BASAL ||
        m_state == PumpState::DELIVERING_BOLUS) {
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

void Pump::deliverBolus(int currentBG, int carbs)
{
    qDebug() << "[Pump] deliverBolus called with BG:" << currentBG << "Carbs:" << carbs;

    if (m_insulin <= 0) {
        emit pumpLog("Error: insulin reservoir empty");
        m_errorHandler->raise(ErrorHandler::LowInsulin, "Insulin empty");
        return;
    }

    if (m_activeProfileIndex < 0) {
        emit pumpLog("Error: no active profile");
        return;
    }

    checkLevels();

    // Build calculator using current IOB
    const Profile &profile = m_profiles[m_activeProfileIndex];
    BolusCalculator calc(
      profile.carbRatio(),
      profile.correctionFactor(),
      m_insulinOnBoard,
      profile.targetBG()
    );

    double foodBolus = calc.foodBolus(static_cast<double>(carbs));
    double corrBolus = calc.correctionBolus(currentBG);
    double required  = foodBolus + corrBolus;
    double finalDose = calc.subtractIOB(required);

    // Cap per-bolus for safety
    const double maxSafeDose = 15.0;
    if (finalDose > maxSafeDose) finalDose = maxSafeDose;

    // Cap to reservoir
    if (finalDose > m_insulin) finalDose = m_insulin;

    if (finalDose <= 0.0) {
        qDebug() << "[Pump] finalDose is zero—skipping.";
        return;
    }

    int unitsDelivered = int(std::round(finalDose));

    // 1) Add to IOB
    m_insulinOnBoard += unitsDelivered;

    // 2) Deduct from reservoir & deliver
    m_insulin -= unitsDelivered;
    emit insulinLevelChanged(m_insulin);
    m_state    = PumpState::DELIVERING_BOLUS;

    logEvent(QString("Bolus delivered: %1 U (food:%2, corr:%3, IOB:%4)")
             .arg(unitsDelivered)
             .arg(foodBolus, 0, 'f', 2)
             .arg(corrBolus, 0, 'f', 2)
             .arg(m_insulinOnBoard, 0, 'f', 2));
    emit pumpLog(QString("Delivered %1 units bolus").arg(unitsDelivered));
    emit bolusDelivered(unitsDelivered, carbs);

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
    // Advance clock
    m_simTime = m_simTime.addSecs(minutes * 60);
    m_totalSimulatedMinutes += minutes;

    // 1) Drain battery
    int chunks     = m_totalSimulatedMinutes / 25;
    int newBattery = std::max(0, 100 - chunks * 5);
    if (newBattery != m_battery) {
        m_battery = newBattery;
        emit batteryLevelChanged(m_battery);
    }

    // 2) Decay IOB linearly over duration
    if (m_insulinOnBoard > 0.0) {
        double decay = (minutes / m_insulinActionDuration) * m_insulinOnBoard;
        m_insulinOnBoard = std::max(0.0, m_insulinOnBoard - decay);
    }

    // 3) Deliver basal if running
    if (m_state == PumpState::DELIVERING_BASAL && m_activeProfileIndex >= 0) {
        const Profile &profile = m_profiles[m_activeProfileIndex];
        double ratePerHour     = profile.basalRate();        // U/hr

        // <-- HERE is the new bit:
        emit basalRateChanged(ratePerHour);

        double unitsThisTick   = ratePerHour * (minutes / 60.0);
        int    deliveredUnits  = int(std::round(unitsThisTick));

        if (deliveredUnits > 0) {
            m_insulin = std::max(0, m_insulin - deliveredUnits);
            logEvent(
              QString("Basal delivered: %1 U over %2 min")
                .arg(deliveredUnits)
                .arg(minutes)
            );
        }
    }

    checkLevels();
}

void Pump::logEvent(const QString &desc)
{
    m_history.append( HistoryLog(m_simTime, desc) );
    emit pumpLog(desc);
}

void Pump::checkLevels()
{
    if (m_battery <= kLowBatteryThreshold)
        m_errorHandler->raise(ErrorHandler::LowBattery,   "Battery low");
    else
        m_errorHandler->clear(ErrorHandler::LowBattery);

    if (m_insulin <= kLowInsulinThreshold)
        m_errorHandler->raise(ErrorHandler::LowInsulin,   "Insulin low");
    else
        m_errorHandler->clear(ErrorHandler::LowInsulin);
}

void Pump::chargeBattery()
{
    int old = m_battery;
    m_battery = std::min(m_battery + 25, 100);
    if (m_battery != old) {
        logEvent(QString("Battery charged to %1 %").arg(m_battery));
        emit batteryLevelChanged(m_battery);
        m_totalSimulatedMinutes = 0;                  // reset drain
        m_errorHandler->clear(ErrorHandler::LowBattery);
    }
}

void Pump::fillInsulin()
{
    m_insulin = 300;
    emit insulinLevelChanged(m_insulin);
    logEvent("Cartridge refilled to 300 U");
    emit pumpLog("Insulin refilled");
    m_errorHandler->clear(ErrorHandler::LowInsulin);
}
