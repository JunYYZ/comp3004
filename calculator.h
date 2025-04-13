#ifndef CALCULATOR_H
#define CALCULATOR_H


class calculator
{
public:
    calculator();
    int calculateTotalBolus();
    int calculateFoodBolus();
    int calculateCorrectionBolus();
    int calculateInsulinOnBoard();
    int calculateImmediateBolus();
    int calculateExtendedBolus();

private:
    int insulinOnBoard;
    int insulinCarbRatio;
    int correctionFactor;
    int targetBG;
    int currentBG;
    int totalBolusReq;
    int bolusDistDuration;
    int immediateBolusFrac;
};

#endif // CALCULATOR_H
