#ifndef BOLUSPAGE_H
#define BOLUSPAGE_H

#include <QWidget>

namespace Ui {
class BolusPage;
}

// forward‐declare your QMainWindow subclass
class mainWindow;
class Pump;

class BolusPage : public QWidget
{
    Q_OBJECT

public:
    /// matches new BolusPage(this)
    explicit BolusPage(mainWindow* mw);
    ~BolusPage() override;

private slots:
    void on_btnDeliver_clicked();
    void updateSuggestion(int carbs);

private:
    Ui::BolusPage* ui;
    mainWindow*    m_mainWindow;
    Pump*          m_pump;
};

#endif // BOLUSPAGE_H
