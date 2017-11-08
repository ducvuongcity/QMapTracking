#ifndef QMAPCONTAINER_H
#define QMAPCONTAINER_H

#include <QLabel>
#include <QMouseEvent>
#include <QToolTip>
#include "common.h"

class QMapContainer : public QLabel
{
    Q_OBJECT

public:
    explicit QMapContainer(QWidget* parent = 0, Qt::WindowFlags f = 0);
    void mousePressEvent(QMouseEvent *ev);

signals:
    void sgnMousePressEvent(const QPoint &globalPoint, const QPoint &localPoint);
};

#endif // QMAPCONTAINER_H
