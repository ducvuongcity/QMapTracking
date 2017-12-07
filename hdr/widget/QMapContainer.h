#ifndef QMAPCONTAINER_H
#define QMAPCONTAINER_H

#include <QLabel>
#include <QMouseEvent>
#include <QToolTip>
#include <QRubberBand>
#include <QtMath>
#include "common.h"

class QMapContainer : public QLabel
{
    Q_OBJECT

private:
    QRubberBand *m_pRubberBand;
    QPoint m_firstPoint;
    QPoint m_secondPoint;

    void createRubberBand(QMouseEvent *ev);

public:
    explicit QMapContainer(QWidget* parent = 0, Qt::WindowFlags f = 0);
    void mousePressEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);
    virtual ~QMapContainer();

signals:
    void sgnMousePressEvent(const QPoint &globalPoint, const QPoint &localPoint);
    void sgnmouseReleaseEvent(const QPoint &firstPoint, const QPoint &secondPoint);
};

#endif // QMAPCONTAINER_H
