#ifndef PUMPINFOPAGE_H
#define PUMPINFOPAGE_H

#include <QWidget>

namespace Ui {
class PumpInfoPage;
}

class PumpInfoPage : public QWidget {
    Q_OBJECT

public:
    explicit PumpInfoPage(QWidget *parent = nullptr);
    ~PumpInfoPage();

    // Setters to populate the fields
    void setSerial(const QString &serial);
    void setSoftwareVersion(const QString &ver);
    void setFirmwareVersion(const QString &ver);

signals:
    void backClicked();

private slots:
    void on_btnBackInfo_clicked();

private:
    Ui::PumpInfoPage *ui;
};

#endif // PUMPINFOPAGE_H
