#include "SimulationClock.h"

SimulationClock::SimulationClock(int realIntervalMs,
                                 int minsPerTick,
                                 QObject* parent)
  : QObject(parent)
  , m_minsPerTick(minsPerTick)
{
    // hook up the QTimer
    m_timer.setSingleShot(false);
    m_timer.setInterval(realIntervalMs);
    connect(&m_timer, &QTimer::timeout, this, &SimulationClock::onTimeout);
}

void SimulationClock::start() {
    m_elapsed = 0;
    m_timer.start();
}

void SimulationClock::onTimeout() {
    m_elapsed += m_minsPerTick;
    emit tick(m_minsPerTick);
}
