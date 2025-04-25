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

enum class PumpState
{
    IDLE,
    DELIVERING_BASAL,
    DELIVERING_BOLUS,
    EMERGENCY_STOP
};

class Pump : public QObject
{
    Q_OBJECT
public:
    explicit Pump(QObject *parent = nullptr);
    const QVector<HistoryLog>& history() const { return m_history; }
    void setSimulationClock(SimulationClock *clock);
    int batteryLevel() const;
    int insulinLevel() const;
    PumpState state() const;
    QVector<Profile> profiles() const;
    void addProfile(const Profile &p);
    bool selectActiveProfile(const QString &name);
    void startInsulin();
    void stopInsulin();
    void resumeInsulin();
    void deliverBolus(int currentBG, int carbs);
    void emergencyStop(const QString &reason);
    void deliverExtendedBolus(double totalUnits, int pctNow, int durationMin);
    double getInsulinOnBoard() const;
    void maybeEmitIOB();
    void logEvent(const QString &desc);

    static constexpr int kLowBatteryThreshold = 20;
    static constexpr int kLowInsulinThreshold = 30;
    static constexpr int kCritLowBGThreshold  = 4;
    static constexpr int kCritHighBGThreshold = 13;

public slots:
    void onSimulatedTimeAdvanced(int minutes);
    void checkLevels();
    void chargeBattery();
    void fillInsulin();

signals:
    void pumpLog(const QString &msg);
    void batteryLevelChanged(int newBattery);
    void reservoirChanged(double newUnits);
    void bolusDelivered(double units, int carbs);
    void warningRaised(ErrorHandler::Warning w, QString msg);
    void warningCleared(ErrorHandler::Warning w);
    void iobChanged(double ewIOB);
    void insulinLevelChanged(int newLevel);
    void basalRateChanged(double newRate);

private:
    struct ActiveDose {
        double units;
        int elapsedMin;
    };

    QVector<ActiveDose> m_iob;
    int m_insulinDuration = 300;  // 5h DIA
    double currentIOB() const;
    void ageAndPruneIOB(int mins);
    int m_battery;
    int m_insulin;
    int m_totalSimulatedMinutes = 0;
    PumpState m_state;
    QVector<Profile> m_profiles;
    int m_activeProfileIndex;
    QVector<HistoryLog> m_history;
    ErrorHandler* m_errorHandler;
    SimulationClock* m_clock = nullptr;
    QDateTime m_simTime;
    double m_cachedIOB = 0.0;
    double m_insulinOnBoard = 0.0;
    double m_insulinActionDuration = 240.0;  // 4 hours (in minutes)
};

#endif // PUMP_H
