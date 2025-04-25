#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QWidget>

namespace Ui {
class HomePage;
}

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
};

#endif // HOMEPAGE_H
