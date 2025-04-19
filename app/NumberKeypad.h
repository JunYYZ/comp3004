#ifndef NUMBERKEYPAD_H
#define NUMBERKEYPAD_H

#include <QWidget>

namespace Ui {
class NumberKeypad;
}

class NumberKeypad : public QWidget
{
    Q_OBJECT

public:
    explicit NumberKeypad(QWidget *parent = nullptr);
    ~NumberKeypad();

signals:
    void digitPressed(int digit);
    void deletePressed();
    void okPressed();

private slots:
    void on_btn0_clicked();
    void on_btn1_clicked();
    void on_btn2_clicked();
    void on_btn3_clicked();
    void on_btn4_clicked();
    void on_btn5_clicked();
    void on_btn6_clicked();
    void on_btn7_clicked();
    void on_btn8_clicked();
    void on_btn9_clicked();
    void on_btnDEL_clicked();
    void on_btnOK_clicked();

private:
    Ui::NumberKeypad *ui;
};

#endif // NUMBERKEYPAD_H
