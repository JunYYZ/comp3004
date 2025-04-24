#pragma once
#include <QObject>
#include <QSet>

class ErrorHandler : public QObject
{
    Q_OBJECT
public:
    enum Warning
    {
        LowBattery = 0,
        LowInsulin = 1,
        BGLow = 2,
        BGHigh = 3
    };
    explicit ErrorHandler(QObject *parent = nullptr);

    void raise(Warning, const QString &msg);
    void clear(Warning);

signals:
    void warningRaised(Warning, QString msg);
    void warningCleared(Warning);

private:
    QSet<Warning> m_active; // <‑‑ keeps track of which warnings are ON
};