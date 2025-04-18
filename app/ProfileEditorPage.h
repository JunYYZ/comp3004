#ifndef PROFILEEDITORPAGE_H
#define PROFILEEDITORPAGE_H

#include <QWidget>
#include "Profile.h"    // your domain class

namespace Ui {
class ProfileEditorPage;
}

class ProfileEditorPage : public QWidget
{
    Q_OBJECT

public:
    explicit ProfileEditorPage(QWidget *parent = nullptr);
    ~ProfileEditorPage() override;

    /// Preload fields to edit an existing profile
    void setProfile(const Profile &p);

signals:
    /// Save the profile (new or edited). The emitted Profile should contain all fields.
    void saveProfile(const Profile &);
    /// Cancel editing and return to list/home
    void cancel();

private slots:
    void onBtnSaveClicked();
    void onBtnCancelClicked();

private:
    Ui::ProfileEditorPage *ui;
    Profile                m_current;
};

#endif // PROFILEEDITORPAGE_H
