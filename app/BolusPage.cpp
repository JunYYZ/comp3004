#include "BolusPage.h"
#include "ui_BolusPage.h"

#include "BolusCalculator.h"
#include "ProfileManager.h"
#include "mainWindow.h"

#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QString>

BolusPage::BolusPage(QWidget *parent)
    : BolusPage(qobject_cast<mainWindow*>(parent)->profileManager(),parent){}


BolusPage::BolusPage(ProfileManager* profileManager,
                     QWidget* parent)
  : QWidget(parent)
  , ui(new Ui::BolusPage)
  , m_profileManager(profileManager)
{
    ui->setupUi(this);

    // Hook up the QDoubleSpinBox for carbs:
    auto doubleSlot =
        static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged);
    connect(ui->sbCarbs, doubleSlot,
            this,        &BolusPage::updateSuggestion);

    // Hook up the QSpinBox for current BG:
    auto intSlot =
        static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged);
    connect(ui->sbCurrentBG, intSlot,
            this,             &BolusPage::updateSuggestion);

    // Initial suggestion on page load
    updateSuggestion();
}

BolusPage::~BolusPage()
{
    delete ui;
}

void BolusPage::updateSuggestion()
{
    // 1) Read inputs
    double carbs = ui->sbCarbs->value();      // grams of carbs
    int    bg    = ui->sbCurrentBG->value();  // current blood glucose
    double iob   = 0.0;                       // TODO: fetch real IOB from history

    // 2) Configure calculator
    BolusCalculator calc;
    auto profile = m_profileManager->activeProfile();
    calc.setCarbRatio(        profile.carbRatio() );
    calc.setCorrectionFactor( profile.correctionFactor() );
    calc.setInsulinOnBoard(   iob );

    // 3) Compute bolus components
    double food   = calc.foodBolus(carbs);
    double corr   = calc.correctionBolus(bg);
    double raw    = food + corr;
    double finalU = calc.subtractIOB(raw);

    // 4) Display result
    ui->lblSuggested->setText(
        tr("Suggest: %1 U")
            .arg(QString::number(finalU, 'f', 1))
    );
}
