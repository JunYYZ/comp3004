
#include "ProfileManager.h"

ProfileManager::ProfileManager(QObject *parent)
    : QObject(parent), m_activeIndex(-1) //no profile yet
{
}

//saj uses this from form button, checks if name exists already
void ProfileManager::addProfile(const Profile &profile)
{
    for (const Profile &p : m_profiles) {
        if (p.name() == profile.name()) {
            emit errorMsg("profile name already exists"); //jun plug in JUN_ERR_DUPLICATE here
            return;
        }
    }

    m_profiles.append(profile);
    if (m_activeIndex == -1)
        m_activeIndex = 0; //first one gets selected auto
    emit profileChanged();
}

//user clicked delete on gui, name passed from selected list
bool ProfileManager::removeProfile(const QString &name)
{
    for (int i = 0; i < m_profiles.size(); ++i) {
        if (m_profiles[i].name() == name) {
            m_profiles.remove(i);
            if (m_activeIndex == i)
                m_activeIndex = -1; //reset selection if deleted
            emit profileChanged();
            return true;
        }
    }
    emit errorMsg("profile not found to remove"); //jun plug in JUN_ERR_NOT_FOUND
    return false;
}

//user modifies values then hits save button, we replace existing one
bool ProfileManager::updateProfile(const QString &name, const Profile &updated)
{
    for (int i = 0; i < m_profiles.size(); ++i) {
        if (m_profiles[i].name() == name) {
            m_profiles[i] = updated;
            emit profileChanged();
            return true;
        }
    }
    emit errorMsg("profile not found to update"); //jun plug in JUN_ERR_NOT_FOUND
    return false;
}

//used to get the full list to show in dropdown or table
QVector<Profile> ProfileManager::profiles() const
{
    return m_profiles;
}

Profile ProfileManager::getProfileByName(const QString &name) const
{
    for (const Profile &p : m_profiles) {
        if (p.name() == name)
            return p;
    }
    // not found: return a dummy
    return Profile("", 0.0, 0.0, 0);
}

//called when user picks from gui dropdown to set active profile
bool ProfileManager::selectProfile(const QString &name)
{
    for (int i = 0; i < m_profiles.size(); ++i) {
        if (m_profiles[i].name() == name) {
            m_activeIndex = i;
            emit profileChanged();
            return true;
        }
    }
    emit errorMsg("could not select profile"); //jun plug in JUN_ERR_NOT_FOUND
    return false;
}

//other ppl use this to pull current settings (michael, nischal etc)
Profile ProfileManager::activeProfile() const
{
    if (m_activeIndex >= 0 && m_activeIndex < m_profiles.size())
        return m_profiles[m_activeIndex];
    return Profile("", 0, 0, 0); //fallback if empty
}

