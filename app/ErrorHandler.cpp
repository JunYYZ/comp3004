#include "ErrorHandler.h"
ErrorHandler::ErrorHandler(QObject *p) : QObject(p) {}
void ErrorHandler::raise(Warning w, const QString &msg) { emit warningRaised(w, msg); }
void ErrorHandler::clear(Warning w) { emit warningCleared(w); }
