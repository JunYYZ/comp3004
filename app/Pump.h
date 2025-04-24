#ifndef PUMP_H
#define PUMP_H

#include <QObject>
#include <QVector>
#include <QString>
#include <QDateTime>

#include "Profile.h"
#include "HistoryLog.h"
#include "BolusCalculator.h"
#include "ErrorHandler.h"

// Forward-declare to avoid circular include
class SimulationClock;

/*─────────────────────────────────────────────────────────────
  Pump operating states
 ─────────────────────────────────────────────────────────────*/
enum class PumpState
{
    IDLE,
    DELIVERING_BASAL,
    DELIVERING_BOLUS,
    EMERGENCY_STOP
};

/*─────────────────────────────────────────────────────────────
  Pump model – core delivery manager
 ─────────────────────────────────────────────────────────────*/
class Pump : public QObject
{
    Q_OBJECT
public:
    explicit Pump(QObject *parent = nullptr);

    // Pump.h  – add this one-liner in the public section
    const QVector<HistoryLog>& history() const { return m_history; }


    /* clock hookup */
    void setSimulationClock(SimulationClock *clock);

    /* simple getters */
    int        batteryLevel() const;
    int        insulinLevel() const;
    PumpState  state()        const;
    QVector<Profile> profiles() const;

    /* profile CRUD */
    void addProfile(const Profile &p);
    bool selectActiveProfile(const QString &name);

    /* basal / bolus control */
    void startInsulin();
    void stopInsulin();
    void resumeInsulin();
    void deliverBolus(int currentBG, int carbs);
    void emergencyStop(const QString &reason);
    /* in the “basal / bolus control” section */
    void deliverExtendedBolus(double totalUnits,
                              int    pctNow,
                              int    durationMin);


    /* IOB public accessor (used by UI) */
    double getInsulinOnBoard() const;     // forward to currentIOB()

    /* thresholds */
    static constexpr int kLowBatteryThreshold = 20;  // %
    static constexpr int kLowInsulinThreshold = 30;  // units
    static constexpr int kCritLowBGThreshold  = 4;   // mmol/L
    static constexpr int kCritHighBGThreshold = 13;  // mmol/L

public slots:
    void onSimulatedTimeAdvanced(int minutes);   // from SimulationClock
    void checkLevels();                          // battery / insulin warnings
    void chargeBattery();                        // +25 %
    void fillInsulin();                          // refill cartridge (300 U)

signals:
    /* high-level status */
    void pumpLog(const QString &msg);
    void batteryLevelChanged(int newBattery);
    void reservoirChanged(double newUnits);

    /* bolus delivered (for CGM/control-IQ) */
    void bolusDelivered(double units, int carbs);

    /* warnings -> GUI pop-ups */
    void warningRaised (ErrorHandler::Warning w, QString msg);
    void warningCleared(ErrorHandler::Warning w);
    void iobChanged(double ewIOB);

private:
    /* event history helper */
    void logEvent(const QString &desc);

    /*────────────  IOB  ────────────*/
    struct ActiveDose          // one bolus “chip”
    {
        double units;          // units delivered
        int    elapsedMin;     // age in simulated minutes
    };
    QVector<ActiveDose> m_iob;      // active bolus list
    int     m_insulinDuration = 300; // 5 h DIA
    double  currentIOB() const;      // live IOB value
    void    ageAndPruneIOB(int mins); // tick helper

    /* battery / reservoir / state */
    int   m_battery;                 // %
    int   m_insulin;                 // units
    int   m_totalSimulatedMinutes=0; // for drain pacing
    PumpState m_state;

    /* profiles */
    QVector<Profile> m_profiles;
    int              m_activeProfileIndex;

    /* logs & helpers */
    QVector<HistoryLog> m_history;
    ErrorHandler*   m_errorHandler;
    SimulationClock*m_clock = nullptr;
    QDateTime       m_simTime;

    double m_cachedIOB = 0.0;
    void maybeEmitIOB();
};

#endif // PUMP_H

