#ifndef CCREADERMANAGER_H
#define CCREADERMANAGER_H

#include <QList>
#include <QFile>

#include "common.h"

class ccReaderManager : public QObject
{
    Q_OBJECT

private:
    static ccReaderManager *s_textReader;
    QList<ccPoint4D> mListMMS;
    ccWorldFile mWorldFile;

    void analysisMMS(QString &path);
    void analysisWorldFile(QString &path);
    void resetWorldFile();

public:
    explicit ccReaderManager(QObject *parent = 0);
    ~ccReaderManager();
    static ccReaderManager *Instance();
    QList<ccPoint4D> &getListMMS();
    ccWorldFile &getWorldFile();
    bool isValidWorldFile();

signals:
    void sgnResponseReadFinished(int type, bool state);

public slots:
    void sltRequestReadHandle(const QString &path, int type);
};

#endif // CCREADERMANAGER_H
