#pragma once
#include <QWidget>
#include "Pump.h"

class Pump;               // fwd
class ProfileManager;

namespace Ui { class BolusPage; }

/*───────────────────────────────────────────────
  Manual / Extended Bolus entry screen
 ───────────────────────────────────────────────*/
class BolusPage : public QWidget
{
    Q_OBJECT
public:
    explicit BolusPage(QWidget* parent = nullptr);
    ~BolusPage() override;

    /* Main-window injects back-end singletons */
    void setProfileManager(ProfileManager* mgr);
    void setPump          (Pump* p) { m_pump = p; }

signals:
    void backClicked();

private slots:
    /* normal bolus */
    void on_btnDeliver_clicked();

    /* NEW - extended bolus */
    void on_btnExt_clicked();             ///< Deliver Extended
    void on_immediatePct_changed(int);    ///< enable/disable Duration

    /* spin-boxes re-calc suggestion */
    void on_carbsSpin_valueChanged(int);
    void on_bgSpin_valueChanged   (int);

    /* back / cancel */
    void onBtnCancelClicked();

private:
    void updateSuggestion();              ///< recompute dose line

    Ui::BolusPage*   ui   = nullptr;
    ProfileManager*  m_profileManager = nullptr;
    Pump*            m_pump           = nullptr;   // hooked in mainWindow
};

