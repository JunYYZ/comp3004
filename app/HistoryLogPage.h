#ifndef HISTORYLOGPAGE_H
#define HISTORYLOGPAGE_H

#include <QWidget>

namespace Ui {
class HistoryLogPage;
}

class mainWindow;
class Pump;

class HistoryLogPage : public QWidget
{
    Q_OBJECT

public:
    explicit HistoryLogPage(QWidget *parent = nullptr);
    ~HistoryLogPage() override;

private slots:
    void addEntry(const QString& msg);
    void on_btnClear_clicked();
    void on_btnBack_clicked();

private:
    Ui::HistoryLogPage* ui;
    mainWindow*         m_mainWindow;
    Pump*               m_pump;
};

#endif // HISTORYLOGPAGE_H
