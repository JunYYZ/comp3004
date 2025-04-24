#include "insulindeliverymanager.h"
#include <QDebug>

InsulinDeliveryManager::InsulinDeliveryManager(QObject *parent)
    : QObject(parent),
      m_state(DeliveryState::Stopped),
      m_activeProfile(""),
      m_basalRate(0.0),
      m_insulinRemaining(300.0)  // Start with a full 300-unit cartridge.
{
    // Set the timer interval: here 1000 ms (1 second), which you can adjust based on your simulation scaling.
    m_deliveryTimer.setInterval(1000);
    connect(&m_deliveryTimer, &QTimer::timeout, this, &InsulinDeliveryManager::onDeliveryTimerTimeout);
}

void InsulinDeliveryManager::setActiveProfile(const QString &profileName, double basalRate)
{
    m_activeProfile = profileName;
    m_basalRate = basalRate;
    emit logEvent(QString("Active profile set: %1 with basal rate %2 U/hr")
                  .arg(m_activeProfile).arg(m_basalRate));
}

bool InsulinDeliveryManager::startDelivery()
{
    // Check if an active profile exists.
    if (m_activeProfile.isEmpty()){
        emit errorOccurred("No active profile set. Please create one first.");
        return false;
    }

    // Check the insulin reservoir level.
    if (m_insulinRemaining < 10.0) {
        emit errorOccurred("Low insulin level. Please refill the insulin reservoir.");
        return false;
    }

    // Prevent starting if already running.
    if (m_state == DeliveryState::Running) {
        emit errorOccurred("Insulin delivery is already running.");
        return false;
    }

    // Begin insulin delivery.
    m_state = DeliveryState::Running;
    m_deliveryTimer.start();
    emit logEvent("Insulin delivery started.");
    emit deliveryStarted();
    return true;
}

bool InsulinDeliveryManager::stopDelivery()
{
    // Only allow stopping if delivery is currently running.
    if (m_state != DeliveryState::Running) {
        emit errorOccurred("Insulin delivery is not running and cannot be stopped.");
        return false;
    }

    m_state = DeliveryState::Paused;
    m_deliveryTimer.stop();
    emit logEvent("Insulin delivery stopped.");
    emit deliveryStopped();
    return true;
}

bool InsulinDeliveryManager::resumeDelivery()
{
    // Resume only if delivery is currently paused.
    if (m_state != DeliveryState::Paused) {
        emit errorOccurred("Insulin delivery is not paused and cannot be resumed.");
        return false;
    }

    // Re-check conditions (e.g., sufficient insulin) before resuming.
    if (m_insulinRemaining < 10.0) {
        emit errorOccurred("Insulin level critically low. Cannot resume delivery.");
        return false;
    }

    m_state = DeliveryState::Running;
    m_deliveryTimer.start();
    emit logEvent("Insulin delivery resumed.");
    emit deliveryResumed();
    return true;
}

void InsulinDeliveryManager::simulateCGMFeedback(double currentBG)
{
    // Log the current CGM reading.
    emit logEvent(QString("Simulated CGM reading: %1 mg/dL").arg(currentBG));

    // Automatically stop insulin delivery if blood glucose falls below a safe threshold.
    if (currentBG < 70) { // Example threshold value.
        if (m_state == DeliveryState::Running) {
            stopDelivery();
            emit logEvent("Automatic stop triggered due to low blood glucose level.");
        }
    }

    // Extend this function to adjust the basal rate dynamically based on Control-IQ algorithms.
}

void InsulinDeliveryManager::checkForErrors()
{
    // Check for low insulin or any other errors that you may add.
    if (m_insulinRemaining < 10.0) {
        emit errorOccurred("Insulin reservoir is critically low.");
    }
    // Additional error checks (e.g., battery or occlusion errors) can be added here.
}

void InsulinDeliveryManager::onDeliveryTimerTimeout()
{
    if (m_state != DeliveryState::Running)
        return;

    // Calculate the dose per tick.
    // For a basal rate (U/hr) and a 1-second timer, dose per tick = basalRate / 3600.
    double dosePerTick = m_basalRate / 3600.0;
    m_insulinRemaining -= dosePerTick;

    emit logEvent(QString("Delivered %1 U. Insulin remaining: %2 U")
                  .arg(dosePerTick, 0, 'f', 4).arg(m_insulinRemaining, 0, 'f', 2));

    // Automatically check for low reservoir level and stop delivery if needed.
    if (m_insulinRemaining < 10.0) {
        emit errorOccurred("Insulin level critically low. Stopping delivery.");
        stopDelivery();
    }
}

