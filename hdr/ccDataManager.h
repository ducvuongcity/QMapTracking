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

private:
    ccDataBuilerImage2DInfo *m_pDBImage2DInfo;
    QList<ccPoint4D> mListMMS;
    QList<QPoint> mListPixel;
    QStringList mListPathImage;
    ccWorldFile mWorldFile;

    void resetWorldFile();
    void sendEvent(EventList event, QString params);

public:
    explicit ccDataManager(QObject *parent = 0);
    ~ccDataManager();
    QList<ccPoint4D> &getListMMS();
    ccWorldFile &getWorldFile();
    QList<QPoint> &getListPixel();
    QStringList &getListPathImage();
    void setListPixel(const QList<QPoint> &list);
    void setListPathImage(const QStringList &list);
    bool isValidWorldFile();
    void analysisMMS(QString &path);
    void analysisWorldFile(QString &path);
    bool notifyChange2DImageInfo(QString &path);
    bool requestFindImagePathByTime(double time, QString &strResult);

signals:
    void sgnResponseReadFinished(int type, bool state);
    void sgnResponseReadStart();
    void udateProgressBarValue(int value);
    void sgnEvent(EventList event, QString params);

public slots:

};

#endif // CCDATAMANAGER_H
