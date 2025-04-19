// HistoryLogPage.h

#ifndef HISTORYLOGPAGE_H
#define HISTORYLOGPAGE_H

#include <QWidget>
namespace Ui { class HistoryLogPage; }
class Pump;

class HistoryLogPage : public QWidget
{
    Q_OBJECT

public:
    // ← this is the new default constructor that QtDesigner (ui_mainWindow.h)
    //    will be able to call:
    explicit HistoryLogPage(QWidget* parent = nullptr);

    // ← your “real” constructor that takes a Pump*
    explicit HistoryLogPage(Pump* pump, QWidget* parent = nullptr);

    ~HistoryLogPage();

signals:
    void backRequested();

private slots:
    void on_btnClear_clicked();
    void on_btnBack_clicked();

public slots:
    void addEntry(const QString& msg);

private:
    Ui::HistoryLogPage* ui;
    Pump*                m_pump;
};

#endif // HISTORYLOGPAGE_H
