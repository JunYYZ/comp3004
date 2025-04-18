#ifndef SETTINGSPAGE_H
#define SETTINGSPAGE_H

#include <QWidget>

struct PumpSettings {
    double maxBolus;
    double maxBasal;
    double minBasal;
    int    lowBGAlarm;
    int    highBGAlarm;
    double lowInsulinAlert;
};

namespace Ui {
class SettingsPage;
}

class SettingsPage : public QWidget {
    Q_OBJECT

public:
    explicit SettingsPage(QWidget *parent = nullptr);
    ~SettingsPage();

    /// Load current settings into the UI
    void loadSettings(const PumpSettings &s);

    /// Read back what the user has set
    PumpSettings currentSettings() const;

signals:
    void saveClicked();
    void cancelClicked();

private:
    Ui::SettingsPage *ui;

private slots:
    void on_btnSave_clicked();
    void on_btnCancel_clicked();
};

#endif // SETTINGSPAGE_H
