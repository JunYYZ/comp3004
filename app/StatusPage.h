#ifndef STATUSPAGE_H
#define STATUSPAGE_H

#include <QWidget>

namespace Ui {
class StatusPage;
}

class StatusPage : public QWidget {
    Q_OBJECT

public:
    explicit StatusPage(QWidget *parent = nullptr);
    ~StatusPage();

    // Methods for MainWindow or Pump to update the display:
    void setCurrentBG(double bg);
    void setInsulinOnBoard(double iob);
    void setBasalRate(double rate);
    void setBatteryLevel(int percent);

signals:
    void startBasal();
    void stopBasal();

private:
    Ui::StatusPage *ui;
};

#endif // STATUSPAGE_H
