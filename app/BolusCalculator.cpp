#include "BolusCalculator.h"

// constructor initializes all four members
BolusCalculator::BolusCalculator(double carbRatio,
                                 double correctionFactor,
                                 double insulinOnBoard,
                                 int    targetBG)
  : m_carbRatio(carbRatio)
  , m_correctionFactor(correctionFactor)
  , m_insulinOnBoard(insulinOnBoard)
  , m_targetBG(targetBG)
{ }

void BolusCalculator::setCarbRatio(double r)            { m_carbRatio = r; }
void BolusCalculator::setCorrectionFactor(double cf)    { m_correctionFactor = cf; }
void BolusCalculator::setInsulinOnBoard(double iob)     { m_insulinOnBoard = iob; }
void BolusCalculator::setTargetBG(int tbg)              { m_targetBG = tbg; }

double BolusCalculator::foodBolus(double carbs) const {
    return carbs / m_carbRatio;
}

double BolusCalculator::correctionBolus(int currentBG) const {
    double delta = currentBG - m_targetBG;
    return delta / m_correctionFactor;
}

double BolusCalculator::subtractIOB(double totalBolus) const {
    return totalBolus - m_insulinOnBoard;
}

double BolusCalculator::totalBolus(double carbs, int currentBG) const {
    double raw = foodBolus(carbs) + correctionBolus(currentBG);
    return subtractIOB(raw);
}

double BolusCalculator::insulinOnBoard() const {
    return m_insulinOnBoard;
}
double BolusCalculator::carbRatio() const {
    return m_carbRatio;
}
double BolusCalculator::correctionFactor() const {
    return m_correctionFactor;
}
int BolusCalculator::targetBG() const {
    return m_targetBG;
}

BolusCalculator::ExtendedBolus
BolusCalculator::splitExtendedBolus(double totalBolus,
                                    double fractionImmediate,
                                    double durationHours) const
{
    fractionImmediate = std::max(0.0, std::min(1.0, fractionImmediate));
    ExtendedBolus eb;
    eb.durationHours = durationHours;
    eb.immediateDose = totalBolus * fractionImmediate;
    eb.extendedDose  = totalBolus - eb.immediateDose;
    return eb;
}
