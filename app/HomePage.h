
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

    /* NEW – mainWindow passes the Pump pointer once */
    void setPump(Pump *p) { m_pump = p; refreshIOB(); }

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

public slots:                   // << NEW
    void refreshIOB();
    void setIOB(double u);// update lblIOB each time it’s called

private:
    Ui::HomePage *ui;
    Pump        *m_pump = nullptr;   // << NEW
};

#endif // HOMEPAGE_H
