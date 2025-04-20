#ifndef HISTORYLOG_H
#define HISTORYLOG_H
#include <QObject>
#include <QDateTime>
struct HistoryEntry
{
    QDateTime ts;
    QString text;
};
class HistoryLog : public QObject
{
    Q_OBJECT
public:
    explicit HistoryLog(QObject *p = nullptr);
    void add(const QString &txt);
    const QList<HistoryEntry> &entries() const { return m_items; }
signals:
    void newEntry(const HistoryEntry &e);

private:
    QList<HistoryEntry> m_items;
};
#endif