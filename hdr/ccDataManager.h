#ifndef CCDATAMANAGER_H
#define CCDATAMANAGER_H

#include <QList>
#include <QFile>

#include "common.h"

class ccDataManager : public QObject
{
    Q_OBJECT

private:
    static ccDataManager *s_textReader;
    QList<ccPoint4D> mListMMS;
    ccWorldFile mWorldFile;

    void analysisMMS(QString &path);
    void analysisWorldFile(QString &path);
    void resetWorldFile();

public:
    explicit ccDataManager(QObject *parent = 0);
    ~ccDataManager();
    static ccDataManager *Instance();
    QList<ccPoint4D> &getListMMS();
    ccWorldFile &getWorldFile();
    bool isValidWorldFile();

signals:
    void sgnResponseReadFinished(int type, bool state);

public slots:
    void sltRequestReadHandle(const QString &path, int type);
};

#endif // CCDATAMANAGER_H
