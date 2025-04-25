#include "BolusPage.h"
#include "ui_BolusPage.h"
#include "ProfileManager.h"
#include <QTime>
#include <QSpinBox>

BolusPage::BolusPage(QWidget* parent)
  : QWidget(parent),
    ui(new Ui::BolusPage),
    m_profileManager(nullptr)
{
    ui->setupUi(this);



    // wire up your spin‐boxes (assuming you named them carbsSpin and bgSpin in Designer)
    connect(ui->sbCarbs, SIGNAL(valueChanged(int)),
            this,          SLOT(on_carbsSpin_valueChanged(int)));
    connect(ui->sbCurrentBG,    SIGNAL(valueChanged(int)),
            this,          SLOT(on_bgSpin_valueChanged(int)));
    connect(ui->btnDeliverNow, &QPushButton::clicked, this, &BolusPage::on_btnDeliver_clicked);
    connect(ui->btnCancel, &QPushButton::clicked,
            this, &BolusPage::onBtnCancelClicked);

    /* ── NEW hooks for extended bolus ────────────────── */
    connect(ui->btnDeliverExt, &QPushButton::clicked,
            this,              &BolusPage::on_btnExt_clicked);          // NEW
    /* just change <int> → <double> and &QDoubleSpinBox::valueChanged */
    connect(ui->spnImmediatePct,
            QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this,
            &BolusPage::on_immediatePct_changed);


    /* ensure Duration enabled|disabled correctly on start */
    on_immediatePct_changed(ui->spnImmediatePct->value());              // NEW

    // initial display
    updateSuggestion();
}

BolusPage::~BolusPage()
{
    delete ui;
}

void BolusPage::setProfileManager(ProfileManager* mgr)
{
    m_profileManager = mgr;
    // once we have a real manager, we can re‐compute
    updateSuggestion();
}

void BolusPage::on_btnDeliver_clicked()
{
  if (!m_profileManager || !m_pump) {
    // still not hooked up correctly
    return;
  }

  // grab the numbers
  int grams     = ui->sbCarbs->value();
  int currentBG = ui->sbCurrentBG->value();

  // calculate suggested bolus just like updateSuggestion()
  auto prof = m_profileManager->activeProfile();
  double carbBolus = grams / prof.carbRatio();
  double corrBolus = (currentBG - prof.targetBG()) / prof.correctionFactor();
  double total     = qMax(0.0, carbBolus + corrBolus);

  // actually deliver it through your pump
  m_pump->deliverBolus(currentBG, grams);

  // give the user a little feedback
  ui->lblSuggested->setText(
    QString::asprintf("Delivered %.1f U", total)
  );
}

void BolusPage::on_carbsSpin_valueChanged(int /*grams*/)
{
    updateSuggestion();
}

void BolusPage::on_bgSpin_valueChanged(int /*bg*/)
{
    updateSuggestion();
}

void BolusPage::updateSuggestion()
{
    if (!m_profileManager) {
        ui->lblSuggested->setText(tr("No profile manager hooked up"));
        return;
    }

    auto profile = m_profileManager->activeProfile();
    double carbRatio       = profile.carbRatio();
    double correctionFact  = profile.correctionFactor();
    int    targetBG        = profile.targetBG();
    int    currentBG       = ui->sbCurrentBG->value();
    int    grams           = ui->sbCarbs->value();

    // simple example: carb bolus + correction
    double carbBolus  = grams / carbRatio;
    double corrBolus  = (currentBG - targetBG) / correctionFact;
    double totalUnits = carbBolus + corrBolus;
    if (totalUnits < 0) totalUnits = 0;

    ui->lblSuggested->setText(
        QString::asprintf("Suggest %.1f U", totalUnits)
    );
}

void BolusPage::onBtnCancelClicked() {
    emit backClicked();
}

/*─────────────────────────────────────────────────────────
  EXTENDED  bolus   ── NEW ───────────────────────────────*/
void BolusPage::on_btnExt_clicked()                                    // NEW
{
    if (!m_profileManager || !m_pump) return;

    /* recompute total units just like updateSuggestion() */
    const Profile& prof = m_profileManager->activeProfile();
    int grams      = ui->sbCarbs->value();
    int currentBG  = ui->sbCurrentBG->value();

    double carbBol = grams / prof.carbRatio();
    double corrBol = (currentBG - prof.targetBG()) / prof.correctionFactor();
    double totalU  = qMax(0.0, carbBol + corrBol);

    /* gather square-wave parameters */
    int pctNow   = ui->spnImmediatePct->value();         // % immediate
    QTime dur    = ui->timeDuration->time();             // hh:mm
    int  minutes = dur.hour()*60 + dur.minute();
    if (minutes == 0) minutes = 5;                       // minimum 1 tick

    /* hand off to Pump */
    m_pump->deliverExtendedBolus(totalU, pctNow, minutes);

    /* user feedback */
    ui->lblSuggested->setText(
        QString::asprintf("Ext %.1f U  (%d%% now)", totalU, pctNow));
}

/*─────────────────────────────────────────────────────────
  %Immediate spin-box toggles Duration  ── NEW ───────────*/
void BolusPage::on_immediatePct_changed(int pct)                      // NEW
{
    bool enable = pct < 100;
    ui->timeDuration->setEnabled(enable);
    updateSuggestion();
}



