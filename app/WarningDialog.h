#ifndef WARNINGDIALOG_H
#define WARNINGDIALOG_H

#pragma once
#include <QDialog>
#include "ErrorHandler.h"

class Pump;    // forward

class WarningDialog : public QDialog
{
    Q_OBJECT
public:
    WarningDialog(ErrorHandler::Warning w,
                  const QString&        msg,
                  Pump*                 pump,
                  QWidget*              parent = nullptr);
};

#endif // WARNINGDIALOG_H
