#ifndef INSULINDELIVERYMANAGER_H
#define INSULINDELIVERYMANAGER_H

#include <QObject>
#include <QTimer>
#include <QString>

// Define the possible states for insulin delivery.
enum class DeliveryState {
    Stopped,
    Running,
    Paused,
    Error
};

class InsulinDeliveryManager : public QObject
{
    Q_OBJECT
public:
    explicit InsulinDeliveryManager(QObject *parent = nullptr);

    // Set the active profile along with its basal rate (units per hour).
    void setActiveProfile(const QString &profileName, double basalRate);

    double getInsulinRemaining() const { return m_insulinRemaining; }

    // Control functions for insulin delivery.
    bool startDelivery();
    bool stopDelivery();
    bool resumeDelivery();

    // Simulate feedback from the CGM for Control-IQ mode (e.g., auto-suspend on low BG).
    void simulateCGMFeedback(double currentBG);

    // Check for additional errors such as low insulin or other conditions.
    void checkForErrors();

signals:
    // Signals for GUI or log updates.
    void deliveryStarted();
    void deliveryStopped();
    void deliveryResumed();
    void errorOccurred(const QString &errorMsg);
    void logEvent(const QString &eventMsg);

private slots:
    // Callback for QTimer to simulate periodic insulin dosing.
    void onDeliveryTimerTimeout();

private:
    DeliveryState m_state;
    QString m_activeProfile;    // Active user profile name.
    double m_basalRate;         // Basal delivery rate (units per hour).
    QTimer m_deliveryTimer;     // Timer to simulate dosing intervals.
    double m_insulinRemaining;  // Simulated insulin reservoir in units.
};

#endif // INSULINDELIVERYMANAGER_H
