#include "BolusPage.h"
#include "ui_BolusPage.h"
#include "ProfileManager.h"

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
