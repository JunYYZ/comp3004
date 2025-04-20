#include "HistoryLog.h"
HistoryLog::HistoryLog(QObject *p) : QObject(p) {}
void HistoryLog::add(const QString &txt)
{
    HistoryEntry e{QDateTime::currentDateTime(), txt};
    m_items.append(e);
    emit newEntry(e);
}