// SimulationClock.cpp
#include "SimulationClock.h"

SimulationClock::SimulationClock(int realIntervalMs,
                                 int simMinutesPerRealInterval,
                                 QObject* parent)
    : QObject(parent),
      m_simMinutesPerTick(simMinutesPerRealInterval),
      m_totalSimMinutes(0)
{
    m_timer.setInterval(realIntervalMs);
    connect(&m_timer, &QTimer::timeout, this, &SimulationClock::onTimeout);
}

void SimulationClock::start() {
    m_timer.start();
}

void SimulationClock::stop() {
    m_timer.stop();
}

int SimulationClock::simulatedMinutes() const {
    return m_totalSimMinutes;
}

void SimulationClock::onTimeout() {
    m_totalSimMinutes += m_simMinutesPerTick;
    emit tick(m_totalSimMinutes);
}
