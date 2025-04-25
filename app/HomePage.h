
#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QWidget>

class Pump;                     // << forward declaration

namespace Ui { class HomePage; }

class HomePage : public QWidget
{
    Q_OBJECT
public:
    explicit HomePage(QWidget *parent = nullptr);
    ~HomePage();


signals:
    void gotoBolus();
    void gotoControlIQ();
    void gotoGraph();
    void gotoHistory();
    void gotoInsulin();
    void loadCartridge();
    void gotoProfiles();
    void gotoPumpInfo();
    void gotoSettings();
    void gotoStatus();

private:
    Ui::HomePage *ui;
    Pump        *m_pump = nullptr;   // << NEW
};

#endif // HOMEPAGE_H
