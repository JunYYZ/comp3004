#include "BGSimulator.h"
#include "Profile.h"

BGSimulator::BGSimulator(QObject* parent) : QObject(parent)
{
}

void BGSimulator::setProfile(const Profile& profile)
{
    carbRatio = profile.getCarbRatio();
    correctionFactor = profile.getCorrectionFactor();
}

void BGSimulator::onBolusDelivered(int bg, int carbs)
{
    // Simulate effect: carbs push BG up, insulin pulls it down
    carbEffect += carbs * 0.1; // e.g. 10g → +1 mmol/L
    activeInsulin += (carbs / carbRatio); // bolus units delivered
}

void BGSimulator::onTick(int /*minutes*/)
{
    // Simulate insulin effect
    currentBG -= activeInsulin * correctionFactor * 0.05;
    activeInsulin *= 0.9; // decay

    // Simulate carb effect
    currentBG += carbEffect * 0.05;
    carbEffect *= 0.9; // digestion slows

    // Clamp BG
    if (currentBG < 3.0) currentBG = 3.0;
    if (currentBG > 20.0) currentBG = 20.0;

    emit newReading(currentBG);
}
