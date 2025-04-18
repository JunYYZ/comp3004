#ifndef LOCKPAGE_H
#define LOCKPAGE_H

#include <QWidget>

namespace Ui {
class LockPage;
}

class LockPage : public QWidget
{
    Q_OBJECT

public:
    explicit LockPage(QWidget *parent = nullptr);
    ~LockPage();

signals:
    void authenticated();     // emitted when PIN OK

private slots:
    void onDigitPressed(int digit);
    void onDeletePressed();
    void onOkPressed();

private:
    Ui::LockPage *ui;
    QString      m_currentPin;
    const QString m_correctPin = "1234";  // your real PIN check
};

#endif // LOCKPAGE_H
