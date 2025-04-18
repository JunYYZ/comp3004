#include "Profile.h"

Profile::Profile(const QString &name,
                 double carbRatio,
                 double correctionFactor,
                 int targetBG)
    : m_name(name),
      m_carbRatio(carbRatio),
      m_correctionFactor(correctionFactor),
      m_targetBG(targetBG)
{}

QString Profile::name() const               { return m_name; }
double  Profile::carbRatio() const          { return m_carbRatio; }
double  Profile::correctionFactor() const   { return m_correctionFactor; }
int     Profile::targetBG() const           { return m_targetBG; }

void Profile::setName(const QString &name)              { m_name = name; }
void Profile::setCarbRatio(double r)                    { m_carbRatio = r; }
void Profile::setCorrectionFactor(double cf)            { m_correctionFactor = cf; }
void Profile::setTargetBG(int tbg)                      { m_targetBG = tbg; }
