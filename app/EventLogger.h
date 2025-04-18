#ifndef EVENTLOGGER_H
#define EVENTLOGGER_H

#include <QObject>
#include <QVector>
#include <QString>
#include "HistoryLog.h"

/**
 * @brief Records timestamped events for later retrieval.
 */
class EventLogger : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Constructs an EventLogger with an optional QObject parent.
     * @param parent  QObject parent (for ownership); defaults to nullptr.
     */
    explicit EventLogger(QObject* parent = nullptr);

    /**
     * @brief Logs a new event with the current timestamp.
     * @param desc  Description of the event.
     */
    void log(const QString& desc);

    /**
     * @brief Returns the list of all logged events.
     */
    QVector<HistoryLog> events() const;

private:
    QVector<HistoryLog> m_events;  ///< Stored history of events
};

#endif // EVENTLOGGER_H
