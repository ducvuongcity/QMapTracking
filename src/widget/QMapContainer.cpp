#include "QMapContainer.h"


QMapContainer::QMapContainer(QWidget *parent, Qt::WindowFlags f)
    : QLabel(parent, f)
{}

void QMapContainer::mousePressEvent(QMouseEvent *ev)
{
//    QToolTip::showText(ev->globalPos(), QString("%1, %2").arg(ev->x()).arg(ev->y()));
    emit sgnMousePressEvent(ev->globalPos(), ev->pos());
}
