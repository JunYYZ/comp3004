#include "HistoryLog.h"

// existing ctor: stamps with current time
HistoryLog::HistoryLog(const QString &desc)
  : m_timestamp(QDateTime::currentDateTime())
  , m_description(desc)
{}

// new ctor: use provided timestamp
HistoryLog::HistoryLog(const QDateTime &ts, const QString &desc)
  : m_timestamp(ts)
  , m_description(desc)
{}

QDateTime HistoryLog::timestamp() const { return m_timestamp; }
QString   HistoryLog::description() const { return m_description; }
