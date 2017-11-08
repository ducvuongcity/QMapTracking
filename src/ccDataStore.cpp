#include "ccDataStore.h"

ccDataStore::ccDataStore(QObject *parent) : QObject(parent)
{}

QList<ccPoint4D> &ccDataStore::getListMMS() const
{
    return m_listMMS;
}

ccWorldFile &ccDataStore::getWorldFile() const
{
    return m_worldFile;
}

QList<QPoint> &ccDataStore::getListPixel()
{
    return m_listPixel;
}

bool ccDataStore::isValidWorldFile()
{
    return (m_worldFile.A != 0.0f) && (m_worldFile.E != 0.0f);
}

void ccDataStore::setListPixel(const QList<QPoint> &list)
{
    m_listPixel.clear();
    for (int i = 0; i < list.size(); ++i)
        m_listPixel.append(list.at(i));
}

