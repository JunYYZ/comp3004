// Pump.cpp  – IOB-enabled version
#include "Pump.h"
#include "SimulationClock.h"

#include <cmath>
#include <algorithm>
#include <QDebug>

inline void Pump::maybeEmitIOB()
{
    double now = currentIOB();
    if (std::fabs(now - m_cachedIOB) >= 0.01) {  // 1 × 0.01 U step
        m_cachedIOB = now;
        emit iobChanged(now);
    }
}


// ────────────────────────────────────────────────────────────
//  Constructor & basic plumbing
// ────────────────────────────────────────────────────────────
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
    // Error-handler plumbing (unchanged)
    m_errorHandler = new ErrorHandler(this);
    connect(m_errorHandler,&ErrorHandler::warningRaised,
            this,             &Pump::warningRaised);
    connect(m_errorHandler,&ErrorHandler::warningCleared,
            this,             &Pump::warningCleared);

    qDebug() << "[Pump] constructed";
    logEvent("Pump initialized");
    checkLevels();
}

// ────────────────────────────────────────────────────────────
//  Clock hookup
// ────────────────────────────────────────────────────────────
void Pump::setSimulationClock(SimulationClock *clk)
{
    if (m_clock)
        disconnect(m_clock,&SimulationClock::tick,
                   this,    &Pump::onSimulatedTimeAdvanced);

    m_clock = clk;

    if (m_clock)
        connect(m_clock,&SimulationClock::tick,
                this,    &Pump::onSimulatedTimeAdvanced);
}

// ────────────────────────────────────────────────────────────
//  Simple getters
// ────────────────────────────────────────────────────────────
int Pump::batteryLevel()  const { return m_battery; }
int Pump::insulinLevel()  const { return m_insulin; }
PumpState Pump::state()   const { return m_state;  }
QVector<Profile> Pump::profiles() const { return m_profiles; }

// ────────────────────────────────────────────────────────────
//  Profile CRUD / selection  (unchanged from your version)
// ────────────────────────────────────────────────────────────
void Pump::addProfile(const Profile &p)
{
    m_profiles.append(p);
    if (m_activeProfileIndex < 0) m_activeProfileIndex = 0;
    logEvent(QString("Profile added: %1").arg(p.name()));
}
bool Pump::selectActiveProfile(const QString &name)
{
    for (int i = 0; i < m_profiles.size(); ++i)
        if (m_profiles[i].name() == name) {
            m_activeProfileIndex = i;
            logEvent(QString("Active profile set → %1").arg(name));
            emit pumpLog(QString("Profile: %1").arg(name));
            return true;
        }
    emit pumpLog("Error: profile not found");  return false;
}

// ────────────────────────────────────────────────────────────
//  IOB helpers  ✱ NEW ✱
// ────────────────────────────────────────────────────────────
double Pump::currentIOB() const
{
    double total = 0.0;
    for (const auto& d : m_iob) {
        double remain = d.units *
               qMax(0.0, 1.0 - double(d.elapsedMin)/m_insulinDuration);
        total += remain;
    }
    return total;
}
void Pump::ageAndPruneIOB(int mins)
{
    for (auto &d : m_iob) d.elapsedMin += mins;
    m_iob.erase(std::remove_if(m_iob.begin(), m_iob.end(),
                [&](const ActiveDose& d){
                    return d.elapsedMin >= m_insulinDuration;
                }),
                m_iob.end());

    maybeEmitIOB();
}


// ────────────────────────────────────────────────────────────
//  Basal start / stop / resume  (logic unchanged)
// ────────────────────────────────────────────────────────────
void Pump::startInsulin()
{

    if (m_state != PumpState::IDLE || m_activeProfileIndex < 0) return;
    m_state = PumpState::DELIVERING_BASAL;
    logEvent("Basal delivery started");
    emit basalRateChanged(m_profiles[m_activeProfileIndex].basalRate());
    emit pumpLog("Basal started");

}
void Pump::stopInsulin()
{
    if (m_state==PumpState::DELIVERING_BASAL
        || m_state==PumpState::DELIVERING_BOLUS) {
        m_state = PumpState::IDLE;
        logEvent("Insulin delivery stopped");
        emit basalRateChanged(0.0);
        emit pumpLog("Delivery stopped");
    }
}
void Pump::resumeInsulin()
{
    if (m_state==PumpState::IDLE && m_activeProfileIndex>=0) {
        m_state = PumpState::DELIVERING_BASAL;
        logEvent("Basal resumed");
        emit basalRateChanged(m_profiles[m_activeProfileIndex].basalRate());
        emit pumpLog("Basal resumed");
    }
}

// ────────────────────────────────────────────────────────────
//  Manual bolus  – now adds to IOB  ✱ NEW LINES MARKED ✱
// ────────────────────────────────────────────────────────────
void Pump::deliverBolus(int currentBG, int carbs)
{

    if (m_activeProfileIndex < 0) { emit pumpLog("Error: no active profile"); return; }
    checkLevels();

    const Profile& pr = m_profiles[m_activeProfileIndex];
    BolusCalculator calc(pr.carbRatio(), pr.correctionFactor(), currentIOB());

    double foodBolus = calc.foodBolus(double(carbs));
    double corrBolus = calc.correctionBolus(double(currentBG));
    double required  = foodBolus + corrBolus;
    double finalDose = calc.subtractIOB(required);

    const double maxSafeDose = 15.0;              // safety clamp
    if (finalDose > maxSafeDose) finalDose = maxSafeDose;
    if (finalDose > m_insulin)   finalDose = m_insulin;
    if (finalDose <= 0.0)        return;

    // --- apply dose ------------------------------------------------
    m_insulin -= int(std::round(finalDose));
    emit reservoirChanged(m_insulin);

    /* ✱ NEW ✱  append to IOB bucket */
    m_iob.append({ finalDose, 0 });
    maybeEmitIOB();

    logEvent(QString("Bolus %1 U  (food:%2  corr:%3  IOB:%4)")
             .arg(finalDose).arg(foodBolus).arg(corrBolus).arg(currentIOB()));
    emit pumpLog(QString("Delivered %1 U bolus").arg(finalDose));
    emit bolusDelivered(finalDose, carbs);


    m_state = PumpState::IDLE;
    checkLevels();
}

// ────────────────────────────────────────────────────────────
//  Simulation-clock callback  – age IOB + battery drain  ✱ NEW ✱
// ────────────────────────────────────────────────────────────
void Pump::onSimulatedTimeAdvanced(int minutes)
{
    m_simTime = m_simTime.addSecs(minutes * 60);
    m_totalSimulatedMinutes += minutes;

    // 1) Age / prune IOB
    ageAndPruneIOB(minutes);

    // 2) Battery drain calculation
    int chunks = m_totalSimulatedMinutes / 25;   // 25 min chunks
    int newBattery = qMax(0, 100 - chunks * 5);
    if (newBattery != m_battery) {
        m_battery = newBattery;
        emit batteryLevelChanged(m_battery);
    }

    // 3) Decay IOB linearly over duration
    if (m_insulinOnBoard > 0.0) {
        double decay = (minutes / m_insulinActionDuration) * m_insulinOnBoard;
        m_insulinOnBoard = std::max(0.0, m_insulinOnBoard - decay);
    }

    // 4) Deliver basal if running
    if (m_state == PumpState::DELIVERING_BASAL && m_activeProfileIndex >= 0) {
        const Profile &profile = m_profiles[m_activeProfileIndex];
        double ratePerHour = profile.basalRate();        // U/hr
        double unitsThisTick = ratePerHour * (minutes / 60.0);
        int deliveredUnits = int(std::round(unitsThisTick));

        if (deliveredUnits > 0) {
            m_insulin = std::max(0, m_insulin - deliveredUnits);
            logEvent(QString("Basal delivered: %1 U over %2 min")
                     .arg(deliveredUnits).arg(minutes));
        }
    }

    checkLevels();
}

// ────────────────────────────────────────────────────────────
//  History & warnings (same as before)
// ────────────────────────────────────────────────────────────
void Pump::logEvent(const QString &desc)
{
    m_history.append( HistoryLog(m_simTime, desc) );
    emit pumpLog(desc);
}
void Pump::checkLevels()
{
    // Check for low battery
    if (m_battery <= kLowBatteryThreshold) {
        m_errorHandler->raise(ErrorHandler::LowBattery, "Battery low");
    } else {
        m_errorHandler->clear(ErrorHandler::LowBattery);
    }

    // Check for low insulin
    if (m_insulin <= kLowInsulinThreshold) {
        m_errorHandler->raise(ErrorHandler::LowInsulin, "Insulin low");
    } else {
        m_errorHandler->clear(ErrorHandler::LowInsulin);
    }

    // Check for low insulin on board
    if (m_insulinOnBoard <= 0.0) {
        m_errorHandler->raise(ErrorHandler::LowInsulin, "Insulin on board depleted");
    }
}

// battery-charge & refill-reservoir remain unchanged
void Pump::chargeBattery()
{
    int old = m_battery;
    m_battery = std::min(m_battery + 25, 100);  // Charge by 25%, max 100%
    if (m_battery != old) {
        logEvent(QString("Battery charged to %1%").arg(m_battery));
        emit batteryLevelChanged(m_battery);
        m_totalSimulatedMinutes = 0;  // Reset simulated time after charging
        m_errorHandler->clear(ErrorHandler::LowBattery);
    }
}

void Pump::fillInsulin()
{
    m_insulin = 300;  // Refill to 300 units
    emit insulinLevelChanged(m_insulin);
    logEvent("Cartridge refilled to 300 U");
    emit pumpLog("Insulin refilled");
    m_errorHandler->clear(ErrorHandler::LowInsulin);
}


// Pump.cpp  – make sure this matches the declaration exactly
double Pump::getInsulinOnBoard() const
{
    return currentIOB();          // helper we already implemented
}

// ---------------------------------------------------------------------------
//  Extended (square-wave) bolus  – TEMP stub so linker succeeds
// ---------------------------------------------------------------------------
void Pump::deliverExtendedBolus(double totalUnits, int pctNow, int durationMin)
{
    // reuse immediate-only logic for now:
    int grams     = 0;
    int currentBG = 0;
    deliverBolus(currentBG, grams);

    // … you need to append your NOW-chunk and then call maybeEmitIOB():
    double nowU = totalUnits * pctNow / 100.0;
    m_iob.append({ nowU, 0 });    // add the ‘now’ chunk
    maybeEmitIOB();               // ← ADD this line

    logEvent(QString("[STUB] Ext-bolus …"));
}






