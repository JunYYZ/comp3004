#include "WarningDialog.h"
#include "Pump.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

WarningDialog::WarningDialog(ErrorHandler::Warning w,
                             const QString&        msg,
                             Pump*                 pump,
                             QWidget*              parent)
    : QDialog(parent)
{
    setWindowTitle("Pump Warning");
    setModal(true);

    auto *lay = new QVBoxLayout(this);
    lay->addWidget(new QLabel(msg, this));

    QPushButton *btn = nullptr;

    switch (w)
    {
    case ErrorHandler::LowBattery:
        btn = new QPushButton("Charge battery", this);
        connect(btn, &QPushButton::clicked, pump, &Pump::chargeBattery);
        break;
    case ErrorHandler::LowInsulin:
        btn = new QPushButton("Fill insulin", this);
        connect(btn, &QPushButton::clicked, pump, &Pump::fillInsulin);
        break;
    case ErrorHandler::BGLow:
        btn = new QPushButton("Stop Pump", this);
        connect(btn, &QPushButton::clicked, pump, &Pump::emergencyStop);
        break;
    case ErrorHandler::BGHigh:
        btn = new QPushButton("Fill insulin", this);
        connect(btn, &QPushButton::clicked, pump, &Pump::deliverBolus);
        break;
    default:                                      // generic warnings
        btn = new QPushButton("Dismiss", this);
        break;
    }

    connect(btn, &QPushButton::clicked, this, &QDialog::accept);
    lay->addWidget(btn);
    resize(250, 120);
}
