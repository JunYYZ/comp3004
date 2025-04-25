#pragma once

#include <QWidget>
#include "Pump.h"
class ProfileManager;

namespace Ui {
class BolusPage;
}

class BolusPage : public QWidget
{
    Q_OBJECT

public:
    explicit BolusPage(QWidget* parent = nullptr);
    ~BolusPage() override;

    /// Must be called by MainWindow to give BolusPage its ProfileManager.
    void setProfileManager(ProfileManager* mgr);
    void setPump(Pump* p) { m_pump = p; }

signals:
    void backClicked();

private slots:
    void on_carbsSpin_valueChanged(int grams);
    void on_bgSpin_valueChanged(int bg);
    void on_btnDeliver_clicked();
    void onBtnCancelClicked();

private:
    void updateSuggestion();

    Ui::BolusPage*    ui;
    ProfileManager*   m_profileManager;
    Pump*            m_pump = nullptr;   // ← new
};
