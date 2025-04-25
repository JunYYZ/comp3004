#include "insulindeliverymanager.h"
#include "SimulationClock.h"
#include <QtMath>
#include <algorithm>

InsulinDeliveryManager::InsulinDeliveryManager(QObject *parent)
    : QObject(parent)
{
    m_basalTimer.setInterval(1000);               // 1 real s ≅ 5 sim min
    connect(&m_basalTimer, &QTimer::timeout,
            this,            &InsulinDeliveryManager::onBasalTick);
}

// ––––– configuration –––––
void InsulinDeliveryManager::setClock(SimulationClock *clk)
{
    /* not used directly here; kept in case you want clock-driven callbacks */
    Q_UNUSED(clk);
}
void InsulinDeliveryManager::setActiveProfile(const QString &name,
                                              double basalRateUph)
{
    m_activeProfile = name;
    m_basalRateUph  = basalRateUph;
    emit logEvent(QString("Active profile set → %1 (%2 U/hr)")
                  .arg(name).arg(basalRateUph,0,'f',2));
}

// ––––– public API –––––
bool InsulinDeliveryManager::startDelivery()
{
    if (m_state == State::Running) {
        emit errorOccurred("Delivery already running");  return false;
    }
    if (m_activeProfile.isEmpty()) {
        emit errorOccurred("No active profile set");     return false;
    }
    if (m_insulinRemaining < 10.0) {
        emit errorOccurred("Insulin critically low");    return false;
    }
    m_state = State::Running;
    m_basalTimer.start();
    emit deliveryStarted();
    emit logEvent("Basal delivery started");
    return true;
}
bool InsulinDeliveryManager::stopDelivery()
{
    if (m_state != State::Running) return false;
    m_state = State::Paused;
    m_basalTimer.stop();
    emit deliveryStopped();
    emit logEvent("Basal delivery paused");
    return true;
}
bool InsulinDeliveryManager::resumeDelivery()
{
    if (m_state != State::Paused) return false;
    if (m_insulinRemaining < 10.0) {
        emit errorOccurred("Insulin too low to resume"); return false;
    }
    m_state = State::Running;
    m_basalTimer.start();
    emit deliveryResumed();
    emit logEvent("Basal delivery resumed");
    return true;
}
void InsulinDeliveryManager::chargeBattery()
{
    m_batteryPercent = qMin(m_batteryPercent + 25, 100);
    emit batteryLevelChanged(m_batteryPercent);
    emit logEvent(QString("Battery charged → %1 %").arg(m_batteryPercent));
}

void InsulinDeliveryManager::deliverBolus(double units)
{
    if (units <= 0.0) return;
    if (units > m_insulinRemaining) units = m_insulinRemaining;

    // subtract from reservoir and add to IOB bucket
    m_insulinRemaining -= units;
    emit reservoirChanged(m_insulinRemaining);

    m_iob.append({ units, 0 });
    emit logEvent(QString("Bolus delivered: %1 U (IOB now %2 U)")
                  .arg(units,0,'f',2).arg(currentIOB(),0,'f',2));
}

void InsulinDeliveryManager::loadCartridge()
{
    m_insulinRemaining = 300.0;
    emit reservoirChanged(m_insulinRemaining);
    emit logEvent("Cartridge loaded → 300 U reservoir");
}

// ––––– computed IOB –––––
double InsulinDeliveryManager::currentIOB() const
{
    double total = 0.0;
    for (const auto& d : m_iob) {
        double remain = d.units *
                        qMax(0.0, 1.0 - double(d.elapsedMin)/m_insulinDuration);
        total += remain;
    }
    return total;
}

// ––––– timer tick –––––
void InsulinDeliveryManager::onBasalTick()
{
    if (m_state != State::Running) return;

    // (1) deliver basal micro-dose (does NOT add to IOB per Tandem docs)
    double dose = m_basalRateUph / 3600.0;
    m_insulinRemaining -= dose;
    emit reservoirChanged(m_insulinRemaining);

    // (2) age & prune active boluses
    ageAndPruneIOB(5);                      // 5 sim min per tick

    // (3) log
    emit logEvent(QString("Basal %1 U; IOB=%2 U; Res=%3 U")
                 .arg(dose,0,'f',5)
                 .arg(currentIOB(),0,'f',2)
                 .arg(m_insulinRemaining,0,'f',1));

    // (4) battery every 10 ticks (~50 sim min)
    if (++m_tickCounter >= 10) {
        m_tickCounter = 0;
        if (m_batteryPercent > 0) {
            --m_batteryPercent;
            emit batteryLevelChanged(m_batteryPercent);
            if (m_batteryPercent <= 5) {
                emit errorOccurred("Battery critically low");
            }
        }
    }

    // safety: auto-stop if reservoir < 10 U
    if (m_insulinRemaining < 10.0) {
        emit errorOccurred("Insulin critically low – auto-stop");
        stopDelivery();
    }
}

// ––––– helper –––––
void InsulinDeliveryManager::ageAndPruneIOB(int mins)
{
    for (auto &d : m_iob) d.elapsedMin += mins;
    m_iob.erase(std::remove_if(m_iob.begin(), m_iob.end(),
                [&](const ActiveDose& d){
                    return d.elapsedMin >= m_insulinDuration;
                }),
                m_iob.end());
}

