#ifndef BOLUSCALCULATOR_H
#define BOLUSCALCULATOR_H

#include <algorithm>

class BolusCalculator
{
public:
    struct ExtendedBolus {
        double durationHours;
        double immediateDose;
        double extendedDose;
    };

    // default ctor with sane defaults
    explicit BolusCalculator(double carbRatio = 1.0,
                             double correctionFactor = 1.0,
                             double insulinOnBoard = 0.0,
                             int    targetBG = 5);

    // setters
    void setCarbRatio(double r);
    void setCorrectionFactor(double cf);
    void setInsulinOnBoard(double iob);
    void setTargetBG(int tbg);

    // getters
    double insulinOnBoard() const;
    double carbRatio() const;
    double correctionFactor() const;
    int targetBG() const;

    // core computations
    double foodBolus(double carbs) const;
    double correctionBolus(int currentBG) const;
    double subtractIOB(double totalBolus) const;

    // convenience: do everything in one call
    double totalBolus(double carbs, int currentBG) const;

    // extended split
    ExtendedBolus splitExtendedBolus(double totalBolus,
                                    double fractionImmediate,
                                    double durationHours) const;

private:
    double m_carbRatio;
    double m_correctionFactor;
    double m_insulinOnBoard;
    int    m_targetBG;
};

#endif // BOLUSCALCULATOR_H
