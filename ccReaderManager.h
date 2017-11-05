#ifndef CCREADERMANAGER_H
#define CCREADERMANAGER_H

#include <QList>
#include <QFile>
#include <QtConcurrent/QtConcurrentRun>

#include "common.h"

class ccReaderManager : public QObject
{
    Q_OBJECT

    enum FinishedType {
        CC_FINISHED_MMS,

    };

private:
    QList<ccPoint4D> mListMMS;

    void analysisMMS(QString path);

public:
    explicit ccReaderManager(QObject *parent = 0);
    static ccReaderManager *Instance();
    QList<ccPoint4D> getListMMS();

signals:
    void sgnReadFinish(FinishedType finishedType);

public slots:
    void sltReadFileMMS(const QString &path);

};

#endif // CCREADERMANAGER_H
