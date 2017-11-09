#ifndef CCBRIDGE_H
#define CCBRIDGE_H

#include <QObject>

class ccBridge : public QObject
{
    Q_OBJECT
public:
    explicit ccBridge(QObject *parent = 0);
    void sendEventToController(QString event);
    void sendEventToModel(QString event);
    void sendEventToView(QString event);

signals:
    void sgnEventToController(QString event);
    void sgnEventToModel(QString event);
    void sgnEventToView(QString event);

public slots:
};

#endif // CCBRIDGE_H
