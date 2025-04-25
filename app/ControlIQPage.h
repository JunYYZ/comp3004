#ifndef CONTROLIQPAGE_H
#define CONTROLIQPAGE_H

#include <QWidget>

namespace Ui {
class ControlIQPage;
}

class ControlIQPage : public QWidget
{
    Q_OBJECT

public:
    explicit ControlIQPage(QWidget *parent = nullptr);
    ~ControlIQPage();

    // Update the on-screen status text: "Active" or "Inactive"
    void setStatus(const QString &status);
    // Update the displayed basal rate (U/hr)
    void setCurrentBasal(double rate);
    // Update the predicted BG in mmol/L
    void setPredictedBG(double bg);


signals:
    void controlIQTurnedOn();  // Emitted when the "Turn On" button is clicked
    void controlIQTurnedOff(); // Emitted when the "Turn Off" button is clicked
    void backClicked();        // Emitted when the back button is clicked

private slots:
    void on_btnTurnOnCIQ_clicked();   // Slot for "Turn On" button
    void on_btnTurnOffCIQ_clicked();  // Slot for "Turn Off" button
    void on_btnBackCIQ_clicked();     // Slot for back button

private:
    Ui::ControlIQPage *ui;
};

#endif // CONTROLIQPAGE_H
