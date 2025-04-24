#pragma once
#include <QObject>
#include <QTimer>
#include <QVector>

class SimulationClock;

class InsulinDeliveryManager : public QObject
{
    Q_OBJECT
public:
    explicit InsulinDeliveryManager(QObject *parent = nullptr);

    // configuration helpers
    void setClock(SimulationClock *clk);
    void setActiveProfile(const QString &name, double basalRateUph);

    // API called by UI / Control-IQ
    bool startDelivery();      // begin basal
    bool stopDelivery();       // pause basal
    bool resumeDelivery();     // continue basal
    void chargeBattery();      // +25 %
    void deliverBolus(double units);          // manual or auto bolus
    void loadCartridge();      // refill reservoir

    // read-only getters
    double currentIOB()   const;   // active insulin in U
    double reservoir()    const { return m_insulinRemaining; }
    int    battery()      const { return m_batteryPercent;  }

signals:
    // UI hooks
    void deliveryStarted();
    void deliveryStopped();
    void deliveryResumed();
    void batteryLevelChanged(int);
    void reservoirChanged(double);
    void errorOccurred(const QString &msg);
    void logEvent(const QString &msg);

private slots:
    void onBasalTick();        // every real 1 s (5 sim min)

private:
    struct ActiveDose { double units; int elapsedMin; };   // age in sim-minutes
    void ageAndPruneIOB(int mins);     // helper

    // data
    enum class State { Stopped, Running, Paused } m_state = State::Stopped;
    QString  m_activeProfile;
    double   m_basalRateUph = 0.0;        // U / hour
    double   m_insulinRemaining = 300.0;  // U
    int      m_batteryPercent   = 100;    // %
    QVector<ActiveDose> m_iob;            // active bolus list
    int      m_insulinDuration  = 300;    // 5 h = 300 min
    int      m_tickCounter      = 0;      // battery drain pacing
    QTimer   m_basalTimer;
};
