#ifndef CCDATAMANAGER_H
#define CCDATAMANAGER_H

#include <QList>
#include <QFile>
#include <QPoint>

#include "common.h"

class ccDataManager : public QObject
{
    Q_OBJECT

private:
    void analysisMMS(QString &path);
    void analysisWorldFile(QString &path);

    void setListPixel(const QList<QPoint> &list);

public:
    explicit ccDataManager(ccBridge &bridge, ccDataStore &store, QObject *parent = 0);
    ~ccDataManager();

public slots:
    void sltEvenHandle(QString event);

private:
    ccBridge *m_bridge;
    ccDataStore *m_dataStore;
};

#endif // CCDATAMANAGER_H
