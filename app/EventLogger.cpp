#include "EventLogger.h"
#include "HistoryLog.h"

EventLogger::EventLogger(QObject* parent)
    : QObject(parent)
{
}

void EventLogger::log(const QString& desc)
{
    // Append a new HistoryLog entry
    m_events.append(HistoryLog(desc));
}

QVector<HistoryLog> EventLogger::events() const
{
    // Return the stored events
    return m_events;
}
