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
#include "SimulationClock.h"

class SimulationClock;

/**
 * @brief States the pump can be in.
 */
enum class PumpState
{
    IDLE,
    DELIVERING_BASAL,
    DELIVERING_BOLUS,
    EMERGENCY_STOP
};

/**
 * @brief Simulates the t:slim insulin pump core logic.
 *        Handles profiles, basal/bolus delivery, logging, and warnings.
 */
class Pump : public QObject
{
    Q_OBJECT

public:
    explicit Pump(QObject* parent = nullptr);

    void setSimulationClock(SimulationClock* clock);

    // --- Getters ---
    int batteryLevel() const;      ///< Battery percentage [0–100]
    int insulinLevel() const;      ///< Insulin units remaining
    PumpState state() const;       ///< Current pump state

    /** @returns the full history of timestamped events */
    const QVector<HistoryLog> history() const { return m_history; }

    // --- Profile Management ---
    void addProfile(const Profile& p);
    QVector<Profile> profiles() const;
    bool selectActiveProfile(const QString& name);

    // --- Insulin Delivery ---
    void startInsulin();                        ///< Begin basal delivery
    void stopInsulin();                         ///< Stop basal or bolus
    void resumeInsulin();                       ///< Resume basal after a stop
    void deliverBolus(int currentBG, int carbs);//< Calculate & deliver a bolus
    void emergencyStop(const QString& reason);   ///< Immediate stop for safety

    double getInsulinOnBoard() const;           ///< Stub: returns active IOB

    // --- Warning thresholds ---
    static constexpr int kLowBatteryThreshold = 20;  ///< %
    static constexpr int kLowInsulinThreshold = 30;  ///< units
    static constexpr int kCritLowBGThreshold  = 4;   ///< mmol/L
    static constexpr int kCritHighBGThreshold = 13;  ///< mmol/L

public slots:
    /**
     * @brief Checks battery & insulin levels and raises/clears warnings.
     *        Intended to be connected to a timer or SimulationClock tick.
     */
    void checkLevels();
    void onSimulatedTimeAdvanced(int minutes);
    void chargeBattery();
    void fillInsulin();

signals:
    /**
     * @brief Emitted any time the pump wants to log a message (e.g., GUI console).
     * @param msg  The log message.
     */
    void pumpLog(const QString& msg);
    void batteryLevelChanged(int newBattery);
    void warningRaised (ErrorHandler::Warning w, QString msg);
    void warningCleared(ErrorHandler::Warning w);


    void bolusDelivered(double units, int carbs);
    void warningRaised (ErrorHandler::Warning w, QString msg);
    void warningCleared(ErrorHandler::Warning w);

private:
    /**
     * @brief Appends a timestamped entry to the internal history.
     * @param desc  Description of the event.
     */
    void logEvent(const QString& desc);


    int m_battery;                    ///< Battery level [%]
    int m_insulin;                    ///< Insulin remaining [units]
    int m_totalSimulatedMinutes = 0;  ///< accumulate
    PumpState m_state;                ///< Current state

    QVector<Profile> m_profiles;      ///< User profiles
    int m_activeProfileIndex;         ///< Active profile index

    QVector<HistoryLog> m_history;    ///< Chronological event history
    ErrorHandler* m_errorHandler;     ///< Raises and clears warnings
    SimulationClock* m_clock = nullptr;
    QDateTime m_simTime;

};

#endif // PUMP_H
