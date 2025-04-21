#include "ErrorHandler.h"

ErrorHandler::ErrorHandler(QObject *p) : QObject(p) {}

void ErrorHandler::raise(Warning w, const QString &msg)
{
    if (m_active.contains(w)) return;          // already active – ignore
    m_active.insert(w);
    emit warningRaised(w, msg);
}

void ErrorHandler::clear(Warning w)
{
    if (!m_active.contains(w)) return;         // already cleared – ignore
    m_active.remove(w);
    emit warningCleared(w);
}