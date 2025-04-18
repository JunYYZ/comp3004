#ifndef PROFILELISTPAGE_H
#define PROFILELISTPAGE_H

#include <QWidget>

namespace Ui {
class ProfileListPage;
}

class ProfileListPage : public QWidget
{
    Q_OBJECT

public:
    explicit ProfileListPage(QWidget *parent = nullptr);
    ~ProfileListPage() override;

    /// Call this to display the current list of profile names
    void setProfiles(const QStringList &names);

signals:
    /// User wants to create a new profile
    void addProfile();
    /// User wants to delete the currently selected profile
    void deleteProfile(const QString &profileName);
    /// User wants to edit the currently selected profile
    void editProfile(const QString &profileName);

private slots:
    void onBtnAddClicked();
    void onBtnDeleteClicked();
    void onBtnEditClicked();

private:
    Ui::ProfileListPage *ui;
};

#endif // PROFILELISTPAGE_H
