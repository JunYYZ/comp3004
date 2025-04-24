#include "CGM.h"
#include <QRandomGenerator>
#include <algorithm>
#include <cmath>

CGM::CGM(int intervalSimMinutes, QObject* parent)
    : QObject(parent),
      m_interval(intervalSimMinutes),
      m_lastBG(6.0) // start at 6.0 mmol/L
{
}

void CGM::onTick(int simMinute) {
    if (simMinute % m_interval == 0) {
        double val = generateValue();
        emit newReading(val);
    }
}

double CGM::generateValue()
{
    // Simple random walk logic:
    int step = QRandomGenerator::global()->bounded(21) - 10;  // [-10, 10]
    double delta = step * 0.1;  // ±1.0 mmol/L
    double newVal = m_lastBG + delta;

    // Clamp between 3.0 and 15.0 mmol/L
    m_lastBG = std::max(3.0, std::min(15.0, newVal));
    return m_lastBG;
}

double CGM::latestBG() const {
    return m_lastBG;
}

void CGM::onBolusEffect(double units)
{
    m_lastBG -= units * 1.5; // crude: each unit lowers BG by 1.5 mmol/L
    m_lastBG = std::max(3.0, m_lastBG);  // clamp minimum
}

