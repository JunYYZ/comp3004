#ifndef PROFILEMANAGER_H
#define PROFILEMANAGER_H

#include <QObject>
#include <QVector>
#include <QString>
#include "Profile.h"

class ProfileManager : public QObject
{
    Q_OBJECT

public:
    explicit ProfileManager(QObject *parent = nullptr); //saj uses this in mainwindow setup

    //saj adds new profile from the ui, this checks for duplicate names
    void addProfile(const Profile &profile);

    //used if user wanna delete something they saved before, maybe add confirm button later
    bool removeProfile(const QString &name);

    //for updating existing profile with new settings, called when name exists
    bool updateProfile(const QString &name, const Profile &updated);

    //lets gui or pump see list of profiles to pick from
    QVector<Profile> profiles() const;

    //saj calls this when user picks a profile to use
    bool selectProfile(const QString &name);

    //michael nischal nimish will use this to pull latest profile info
    Profile activeProfile() const;

    Profile getProfileByName(const QString &name) const;

signals:
    void profileChanged(); //for gui refresh dropdown or profile summary view

    //jun has to make error class for this later with codes i call like JUN_ERR_DUPLICATE or JUN_ERR_NOT_FOUND
    void errorMsg(const QString &msg);

private:
    QVector<Profile> m_profiles; //store all profiles
    int m_activeIndex; //-1 if not selected, set to 0 by default when first profile is added
};

#endif // PROFILEMANAGER_H
