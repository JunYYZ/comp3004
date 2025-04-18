#include "NumberKeypad.h"
#include "ui_NumberKeypad.h"

NumberKeypad::NumberKeypad(QWidget* parent)
  : QWidget(parent),
    ui(new Ui::NumberKeypad)
{
    ui->setupUi(this);
}

NumberKeypad::~NumberKeypad()
{
    delete ui;
}

// Digit buttons
#define DIGIT_SLOT(N) \
void NumberKeypad::on_btn##N##_clicked() { emit digitPressed(N); }

DIGIT_SLOT(0)
DIGIT_SLOT(1)
DIGIT_SLOT(2)
DIGIT_SLOT(3)
DIGIT_SLOT(4)
DIGIT_SLOT(5)
DIGIT_SLOT(6)
DIGIT_SLOT(7)
DIGIT_SLOT(8)
DIGIT_SLOT(9)

#undef DIGIT_SLOT

// Backspace
void NumberKeypad::on_btnDel_clicked()
{
    emit deletePressed();
}

// OK
void NumberKeypad::on_btnOK_clicked()
{
    emit okPressed();
}
