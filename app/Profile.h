#ifndef PROFILE_H
#define PROFILE_H

#include <QString>

class Profile
{
public:
    Profile(const QString &name,
            double carbRatio,
            double correctionFactor,
            int targetBG,
            double basalRate);

    QString name() const;
    double carbRatio() const;
    double correctionFactor() const;
    int targetBG() const;

    void setName(const QString &name);
    void setCarbRatio(double r);
    void setCorrectionFactor(double cf);
    void setTargetBG(int tbg);
    double basalRate() const;
    void   setBasalRate(double b);

private:
    QString m_name;
    double  m_carbRatio;
    double  m_correctionFactor;
    int     m_targetBG;
    double m_basalRate;
};

#endif // PROFILE_H
