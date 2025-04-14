#ifndef BOLUSCALCULATOR_H
#define BOLUSCALCULATOR_H

class ExtendedBolus
{
public:
    // Constructor
    ExtendedBolus(double immediateDose, double extendedDose, double durationHrs);

    // Getters
    double getImmediateDose() const;
    double getExtendedDose() const;
    double getDurationHrs() const;

private:
    double m_immediateDose;  // Units to deliver immediately
    double m_extendedDose;   // Units to deliver over time
    double m_durationHrs;  // How many hours for the extended portion
};

/**
 * @brief BolusCalculator class
 *
 * This class encapsulates the math for:
 *  1) Food bolus (carb counting)
 *  2) Correction bolus (based on current BG vs target)
 *  3) Subtracting insulin on board (IOB)
 *  4) Splitting into immediate and extended bolus doses
 */
class BolusCalculator
{
public:
    /**
     * @brief BolusCalculator constructor
     * @param insulinSensitivity (units per mmol/L) - how many units needed to lower 1 mmol/L
     * @param carbRatio (units per gram) - how many units for each gram of carbs
     * @param targetBG (mmol/L) - target blood glucose
     */
    BolusCalculator(double insulinSensitivity, double carbRatio, double targetBG);

    /**
     * @brief Calculates insulin needed for food intake
     * @param carbs (grams)
     * @return units of insulin for the given carbs
     */
    double calculateFoodBolus(double carbs) const;

    /**
     * @brief Calculates correction bolus for a high BG
     * @param currentBG (mmol/L)
     * @return units of insulin for correction (0 if currentBG <= targetBG)
     */
    double calculateCorrectionBolus(double currentBG) const;

    /**
     * @brief Subtract active insulin on board from required bolus
     * @param requiredBolus (units)
     * @param iob (units)
     * @return final bolus after subtracting IOB (>= 0)
     */
    double subtractIOB(double requiredBolus, double iob) const;

    /**
     * @brief Splits total bolus into immediate and extended portions
     * @param totalBolus (units) - total insulin dose
     * @param fractionImmediate [0..1] - fraction of total delivered immediately
     * @param durationHrs - how many hours to spread the extended portion
     * @return ExtendedBolus object with immediate and extended doses
     */
    ExtendedBolus splitExtendedBolus(double totalBolus,
                                     double fractionImmediate,
                                     double durationHrs) const;

private:
    double m_correctionFactor; // e.g., 1.0 => 1 unit per 1 mmol/L difference
    double m_carbRatio;         // e.g., 10.0 => 1 unit for every 10g carbs
    double m_targetBG;          // e.g., 5.0 mmol/L
};

#endif // BOLUSCALCULATOR_H
