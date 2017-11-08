#ifndef CCDATASTORE_H
#define CCDATASTORE_H

#include "common.h"

class ccDataStore : public QObject
{
    Q_OBJECT
public:
    explicit ccDataStore(QObject *parent = 0);

    QList<ccPoint4D> &getListMMS() const;
    ccWorldFile &getWorldFile() const;
    QList<QPoint> &getListPixel();
    bool isValidWorldFile();

private:
    QList<ccPoint4D> m_listMMS;
    QList<QPoint> m_listPixel;
    ccWorldFile m_worldFile;
};

#endif // CCDATASTORE_H
