#ifndef CCDATAMANAGER_H
#define CCDATAMANAGER_H

#include <QList>
#include <QFile>
#include <QPoint>

#include "common.h"
#include "ccDataBuilerImage2DInfo.h"

class ccDataManager : public QObject
{
    Q_OBJECT

// ADD-START QMapTracking 2017.11.18 dhthong
private:
    ccDataBuilerImage2DInfo *m_pDBImage2DInfo;
// ADD-END QMapTracking 2017.11.18 dhthong

    QList<ccPoint4D> mListMMS;
    QList<QPoint> mListPixel;
    ccWorldFile mWorldFile;

    void resetWorldFile();
    void sendEvent(EventList event, QString params);

public:
    explicit ccDataManager(QObject *parent = 0);
    ~ccDataManager();
    QList<ccPoint4D> &getListMMS();
    ccWorldFile &getWorldFile();
    QList<QPoint> &getListPixel();
    void setListPixel(const QList<QPoint> &list);
    bool isValidWorldFile();
    void analysisMMS(QString &path);
    void analysisWorldFile(QString &path);

// ADD-START QMapTracking 2017.11.18 dhthong
    bool notifyChange2DImageInfo(QString &path);
    bool requestFindImagePathByTime(double time, QString &strResult);
// ADD-END QMapTracking 2017.11.18 dhthong
signals:
    void sgnResponseReadFinished(int type, bool state);
    void sgnResponseReadStart();
    void udateProgressBarValue(int value);

    void sgnEvent(EventList event, QString params);

public slots:

};

#endif // CCDATAMANAGER_H
