#ifndef PUMP_H
#define PUMP_H

#include <QObject>
#include <QVector>
#include <QString>
#include "Profile.h"
#include "HistoryLog.h"

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

    // Basic properties
    int batteryLevel() const;
    int insulinLevel() const;
    PumpState state() const;

    // Profiles
    void addProfile(const Profile &p);
    QVector<Profile> profiles() const;
    bool selectActiveProfile(const QString &name);

    // Basic operations
    void startInsulin();
    void stopInsulin();
    void resumeInsulin();
    void deliverBolus(int currentBG, int carbs);

    void emergencyStop(const QString &reason);

signals:
    void pumpLog(const QString &msg); // connect to GUI logs

private:
    void logEvent(const QString &desc);

private:
    int m_battery;
    int m_insulin;
    PumpState m_state;

    QVector<Profile> m_profiles;
    int m_activeProfileIndex; // -1 if none

    QVector<HistoryLog> m_history;
};

#endif // PUMP_H
