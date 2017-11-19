#ifndef QMAPCONTAINER_H
#define QMAPCONTAINER_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <QToolTip>
#include "common.h"
#include "ccImageView.h"

class QMapContainer : public QGraphicsView
{
    Q_OBJECT

public:
    explicit QMapContainer(QWidget* parent = 0);


signals:


public slots:
    void drawMMSHandle(QGraphicsPolygonItem *item);

private:
    ccImageView *sceneMap = nullptr;
};

#endif // QMAPCONTAINER_H
