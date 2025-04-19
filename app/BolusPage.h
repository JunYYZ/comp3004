#ifndef BOLUSPAGE_H
#define BOLUSPAGE_H

#include <QWidget>
class ProfileManager;

namespace Ui {
class BolusPage;
}

class BolusPage : public QWidget
{
    Q_OBJECT

public:
    // This must match BolusPage::BolusPage(ProfileManager*, QWidget*)
    explicit BolusPage(ProfileManager* profileManager,
                       QWidget* parent = nullptr);
    ~BolusPage() override;

private slots:
    void updateSuggestion();

private:
    Ui::BolusPage*    ui;
    ProfileManager*   m_profileManager;  //<— add this
};

#endif // BOLUSPAGE_H
