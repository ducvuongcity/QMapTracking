#include "QMapContainer.h"


QMapContainer::QMapContainer(QWidget *parent)
    : QGraphicsView(parent)
{
    sceneMap = new ccImageView(this);
    setScene(sceneMap);
}

void QMapContainer::drawMMSHandle(QGraphicsPolygonItem *item)
{
    MACRO_THR_DLOG << "drawMMSHandle";
    sceneMap->addItem(item);
}
