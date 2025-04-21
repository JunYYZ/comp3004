#include "BGSimulator.h"
#include <QDebug>
#include <algorithm>
#include <cmath>

BGSimulator::BGSimulator(QObject* parent)
    : QObject(parent) {}

void BGSimulator::setProfile(const Profile& profile) {
    this->carbRatio = profile.carbRatio();
    this->correctionFactor = profile.correctionFactor();
    qDebug() << "[BGSim] Profile set: CR =" << carbRatio << ", CF =" << correctionFactor;
}

void BGSimulator::onBolusDelivered(double units, int carbs) {
    activeInsulin += units;
    double mmolFromCarbs = carbs / carbRatio;
    carbEffect += mmolFromCarbs;
    qDebug() << "[BGSim] Bolus received: " << units << "u, Carbs:" << carbs
             << "-> Added " << mmolFromCarbs << " mmol from carbs.";
}

void BGSimulator::onTick() {
    if (correctionFactor <= 0 || carbRatio <= 0) {
        qWarning() << "[BGSim] Invalid profile settings: CF or CR is zero.";
        return;
    }

    double carbAbsorbRate = 15.0;
    double carbAbsorbed = std::min(carbEffect, carbAbsorbRate);
    double carbRise = carbAbsorbed * (1.0 / carbRatio);
    carbEffect -= carbAbsorbed;

    double insulinUsed = activeInsulin * 0.05;
    double insulinDrop = insulinUsed * (1.0 / correctionFactor);
    activeInsulin -= insulinUsed;

    double deltaBG = carbRise - insulinDrop;
    currentBG = std::clamp(currentBG + deltaBG, 2.0, 15.0);

    qDebug() << "[Graph] Logging BG:" << currentBG
             << "| Insulin:" << activeInsulin
             << "| CarbEffect:" << carbEffect
             << "| ΔBG: + " << carbRise << " - " << insulinDrop << " = " << deltaBG;

    emit newReading(currentBG);
}
