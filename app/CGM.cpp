// CGM.cpp
#include "CGM.h"
#include <QRandomGenerator>
#include <algorithm>

CGM::CGM(int intervalSimMinutes, QObject* parent)
    : QObject(parent), m_interval(intervalSimMinutes)
{
}

void CGM::onTick(int simMinute) {
    if (simMinute % m_interval == 0) {
        double val = generateValue();
        emit newReading(val);
    }
}

// Simple random walk or placeholder
#include <cmath>
double CGM::generateValue()
{
    static double last = 6.0;

    // Generate a random integer in [–10, +10]:
    int step = QRandomGenerator::global()->bounded(21) - 10;
    // Convert to ±1.0 mmol/L range:
    double delta = step * 0.1;

    double newVal = last + delta;

    // Clamp between 3.0 and 15.0 mmol/L:
    last = std::max(3.0, std::min(15.0, newVal));

    return last;
}
