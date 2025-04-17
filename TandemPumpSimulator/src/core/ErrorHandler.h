#ifndef ERRORHANDLER_H
#define ERRORHANDLER_H
#include <QObject>
class ErrorHandler : public QObject
{
    Q_OBJECT
public:
    enum Warning
    {
        LowBattery,
        LowInsulin,
        CritLowBG,
        CritHighBG
    };
    Q_ENUM(Warning)
    explicit ErrorHandler(QObject *p = nullptr);
    void raise(Warning w, const QString &msg);
    void clear(Warning w);
signals:
    void warningRaised(Warning, QString);
    void warningCleared(Warning);
};
#endif