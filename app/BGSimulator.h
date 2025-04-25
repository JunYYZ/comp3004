#ifndef BGSIMULATOR_H
#define BGSIMULATOR_H

#include <QObject>
#include "Profile.h"
//Test
class BGSimulator : public QObject {
    Q_OBJECT

public:
    explicit BGSimulator(QObject* parent = nullptr);
    void setProfile(const Profile& profile);

public slots:
    void onBolusDelivered(double units, int carbs);
    void onTick();

signals:
    void newReading(double glucose);

private:
    double currentBG = 6.0;
    double activeInsulin = 0.0;
    double carbEffect = 0.0;

    double carbRatio = 10.0;
    double correctionFactor = 2.0;

    int currentTimeStep = 0;
};

#endif // BGSIMULATOR_H
