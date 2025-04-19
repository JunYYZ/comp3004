#ifndef PROFILEEDITORPAGE_H
#define PROFILEEDITORPAGE_H

#include <QWidget>
#include "Profile.h"

namespace Ui {
class ProfileEditorPage;
}

class ProfileManager;

class ProfileEditorPage : public QWidget
{
    Q_OBJECT

public:
    /// Edit an existing profile or add a new one (requires a ProfileManager)
    explicit ProfileEditorPage(ProfileManager* manager,
                               QWidget* parent = nullptr);

    /// Default constructor for stacked‑widget usage; you'll need to call setProfileManager() later
    explicit ProfileEditorPage(QWidget* parent = nullptr);

    ~ProfileEditorPage() override;

    /// Switch between “adding new” and “editing existing”
    enum class Mode { New, Edit };
    void setMode(Mode m);
    Mode mode() const;

    /// Pre‑load this page with an existing profile (automatically switches to Edit mode)
    void setProfile(const Profile& p);

    /// If you used the default ctor, inject your ProfileManager before saving
    void setProfileManager(ProfileManager* mgr);

signals:
    /// Emitted when the user clicks Save in New mode
    void addProfile(const Profile& p);
    /// Emitted when the user clicks Save in Edit mode
    void updateProfile(const QString& originalName, const Profile& p);
    /// Emitted when the user clicks Cancel
    void cancel();

private slots:
    void onBtnSaveClicked();
    void onBtnCancelClicked();

private:
    void loadProfileIntoUi();
    void collectUiIntoProfile();
    void updateUiForMode();

    Ui::ProfileEditorPage* ui;
    ProfileManager*        m_profileManager = nullptr;
    Profile                m_current;
    Mode                   m_mode          = Mode::New;
    QString                m_originalName;
};

#endif // PROFILEEDITORPAGE_H
