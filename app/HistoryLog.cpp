// HistoryLog.cpp

#include "HistoryLog.h"
#include <QDateTime>

/**
 * @brief Constructs a new HistoryLog entry with the current timestamp.
 * @param desc  A human‑readable description of the event.
 */
HistoryLog::HistoryLog(const QString &desc)
    : m_timestamp(QDateTime::currentDateTime()),
      m_description(desc)
{
}

/**
 * @brief Returns the timestamp when this log entry was created.
 */
QDateTime HistoryLog::timestamp() const
{
    return m_timestamp;
}

/**
 * @brief Returns the description text for this log entry.
 */
QString HistoryLog::description() const
{
    return m_description;
}
