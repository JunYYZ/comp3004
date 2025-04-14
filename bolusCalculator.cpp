#include "bolusCalculator.h"
#include <algorithm> // for std::max

/*****************
 * ExtendedBolus *
 *****************/

ExtendedBolus::ExtendedBolus(double immediateDose, double extendedDose, double durationHrs)
    : m_immediateDose(immediateDose),
      m_extendedDose(extendedDose),
      m_durationHrs(durationHrs)
{}

double ExtendedBolus::getImmediateDose() const
{
    return m_immediateDose;
}

double ExtendedBolus::getExtendedDose() const
{
    return m_extendedDose;
}

double ExtendedBolus::getDurationHrs() const
{
    return m_durationHrs;
}


/********************
 * BolusCalculator  *
 ********************/

BolusCalculator::BolusCalculator(double correctionFactor, double carbRatio, double targetBG)
    : m_correctionFactor(correctionFactor),
      m_carbRatio(carbRatio),
      m_targetBG(targetBG)
{
}

double BolusCalculator::calculateFoodBolus(double carbs) const
{
    // Example: carbRatio = 10 => 1 unit per 10g carbs
    // If carbs = 50g, then 50 / 10 = 5 units
    if (m_carbRatio <= 0.0) {
        return 0.0; // Avoid division by zero or negative ratio
    }
    return (carbs / m_carbRatio);
}

double BolusCalculator::calculateCorrectionBolus(double currentBG) const
{
    // Example: if (currentBG - targetBG) = 2 mmol/L,
    // and insulinSensitivity = 1.0 => 2 / 1.0 = 2 units
    double diff = currentBG - m_targetBG;
    if (diff <= 0.0) {
        // BG is at or below target, so no correction
        return 0.0;
    }
    if (m_correctionFactor <= 0.0) {
        return 0.0; // Avoid division by zero or negative
    }
    return (diff / m_correctionFactor);
}

double BolusCalculator::subtractIOB(double requiredBolus, double iob) const
{
    // If requiredBolus = 10 units and IOB = 3 units => 7 units final
    // Clamping at 0 to avoid negative dosage
    double finalBolus = requiredBolus - iob;
    return std::max(0.0, finalBolus);
}

ExtendedBolus BolusCalculator::splitExtendedBolus(double totalBolus,
                                                  double fractionImmediate,
                                                  double durationHrs) const
{
    // fractionImmediate should be between 0 and 1
    if (fractionImmediate < 0.0) fractionImmediate = 0.0;
    if (fractionImmediate > 1.0) fractionImmediate = 1.0;

    // Negative or zero duration doesn't make sense for extended portion
    if (durationHrs < 0.0) {
        durationHrs = 0.0;
    }

    // Calculate immediate vs. extended
    double immediate = totalBolus * fractionImmediate;
    double extended  = totalBolus - immediate; // The rest

    // Construct and return an ExtendedBolus object
    return ExtendedBolus(immediate, extended, durationHrs);
}
