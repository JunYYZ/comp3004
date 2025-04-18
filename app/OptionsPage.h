#ifndef OPTIONSPAGE_H
#define OPTIONSPAGE_H

#include <QWidget>

namespace Ui {
class OptionsPage;
}

class OptionsPage : public QWidget
{
    Q_OBJECT

public:
    explicit OptionsPage(QWidget *parent = nullptr);
    ~OptionsPage() override;

signals:
    /// User clicked “Load Cartridge”
    void loadCartridge();
    /// User clicked “Start/Stop Insulin”
    void startStopInsulin();

private slots:
    void onBtnLoadCartridgeClicked();
    void onBtnStartStopInsulinClicked();

private:
    Ui::OptionsPage *ui;
};

#endif // OPTIONSPAGE_H
