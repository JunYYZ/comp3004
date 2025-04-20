#ifndef PROFILELISTPAGE_H
#define PROFILELISTPAGE_H

#include <QWidget>

class ProfileManager;

namespace Ui {
class ProfileListPage;
}

class ProfileListPage : public QWidget
{
    Q_OBJECT

public:
    explicit ProfileListPage(QWidget *parent = nullptr);
    ~ProfileListPage();

    // Inject the ProfileManager once you're ready
    void setProfileManager(ProfileManager* mgr);

signals:
    void requestAddProfile();
    void requestEditProfile(const QString &name);
    void requestDeleteProfile(const QString &name);
    void backRequested();
    void requestActivateProfile(const QString&);

private slots:
    void onBtnAddClicked();
    void onBtnEditClicked();
    void onBtnDeleteClicked();
    void refreshProfiles();               // reload names from the manager
    void onBtnBackClicked();
    void onBtnActivateClicked();

private:
    Ui::ProfileListPage *ui;
    ProfileManager      *m_profileManager = nullptr;
};

#endif // PROFILELISTPAGE_H
