#include "LockPage.h"
#include "ui_LockPage.h"
#include "NumberKeypad.h"

LockPage::LockPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LockPage)
{
    ui->setupUi(this);

    // Wire up keypad signals:
    connect(ui->keypadPlaceholder, &NumberKeypad::digitPressed,  this, &LockPage::onDigitPressed);
    connect(ui->keypadPlaceholder, &NumberKeypad::deletePressed, this, &LockPage::onDeletePressed);
    connect(ui->keypadPlaceholder, &NumberKeypad::okPressed,     this, &LockPage::onOkPressed);

    // clear display
    ui->lblPinDisplay->setText("");
}

LockPage::~LockPage()
{
    delete ui;
}

void LockPage::onDigitPressed(int digit)
{
    if (m_currentPin.length() < 6) {                // limit length if you like
        m_currentPin += QChar('0' + digit);
        ui->lblPinDisplay->setText(m_currentPin);
        ui->lblMessage->clear();
    }
}

void LockPage::onDeletePressed()
{
    if (!m_currentPin.isEmpty()) {
        m_currentPin.chop(1);
        ui->lblPinDisplay->setText(m_currentPin);
    }
}

void LockPage::onOkPressed()
{
    if (m_currentPin == m_correctPin) {
        ui->lblMessage->setText("");    // clear any error
        emit authenticated();
    } else {
        ui->lblMessage->setText("Invalid PIN");
        m_currentPin.clear();
        ui->lblPinDisplay->setText("");
    }
}
