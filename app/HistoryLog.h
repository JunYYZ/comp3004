#ifndef HISTORYLOG_H
#define HISTORYLOG_H

#include <QString>
#include <QDateTime>

class HistoryLog
{
public:
    // existing single‐arg ctor
    explicit HistoryLog(const QString &desc);

    // new two‐arg ctor
    HistoryLog(const QDateTime &ts, const QString &desc);

    QDateTime timestamp() const;
    QString   description() const;

private:
    QDateTime m_timestamp;
    QString   m_description;
};

#endif // HISTORYLOG_H
