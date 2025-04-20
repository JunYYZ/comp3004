// ControlIQPage.h
#ifndef CONTROLIQPAGE_H
#define CONTROLIQPAGE_H

#include <QWidget>

namespace Ui { class ControlIQPage; }

class ControlIQPage : public QWidget {
    Q_OBJECT

public:
    explicit ControlIQPage(QWidget *parent = nullptr);
    ~ControlIQPage();

    void setStatus(const QString &status);
    void setCurrentBasal(double rate);
    void setPredictedBG(double bg);
    void setNextAdjustment(const QString &adj);

signals:
    void toggleClicked();
    void backClicked();

private slots:
    void on_btnToggleCIQ_clicked();
    void on_btnBackCIQ_clicked();

private:
    Ui::ControlIQPage *ui;
};

#endif // CONTROLIQPAGE_H
