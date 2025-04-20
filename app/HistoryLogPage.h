// HistoryLogPage.h

#ifndef HISTORYLOGPAGE_H
#define HISTORYLOGPAGE_H

#include <QWidget>
#include "SimulationClock.h"

namespace Ui { class HistoryLogPage; }
class Pump;

class HistoryLogPage : public QWidget
{
    Q_OBJECT

public:
    /// Default ctor (no pump yet)
    explicit HistoryLogPage(QWidget* parent = nullptr);

    /// “Real” ctor where you immediately inject a Pump
    explicit HistoryLogPage(Pump* pump, QWidget* parent = nullptr);

    ~HistoryLogPage();

    /// Inject your SimulationClock so we can timestamp in sim‑time
    void setSimulationClock(SimulationClock* clock);

signals:
    /// user tapped back
    void backRequested();

private slots:
    void on_btnClear_clicked();
    void on_btnBack_clicked();

public slots:
    /// Called whenever Pump emits pumpLog(...)
    void addEntry(const QString& msg);

private:
    Ui::HistoryLogPage* ui;
    Pump*                m_pump   = nullptr;
    SimulationClock*     m_clock  = nullptr;
};

#endif // HISTORYLOGPAGE_H
