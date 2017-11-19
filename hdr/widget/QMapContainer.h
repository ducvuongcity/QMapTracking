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
// ADD-START QMapTracking 2017.11.18 dhthong
private:
    QRubberBand *m_pRubberBand;
    QPoint m_firstPoint;
private:
    void createRubberBand(QMouseEvent *ev);
// ADD-END QMapTracking 2017.11.18 dhthong
public:
    explicit QMapContainer(QWidget* parent = 0, Qt::WindowFlags f = 0);
    void mousePressEvent(QMouseEvent *ev);
// ADD-START QMapTracking 2017.11.18 dhthong
    void mouseMoveEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);
    virtual ~QMapContainer();
// ADD-END QMapTracking 2017.11.18 dhthong
signals:
    void sgnMousePressEvent(const QPoint &globalPoint, const QPoint &localPoint);
// ADD-START QMapTracking 2017.11.18 dhthong
    void sgnmouseReleaseEvent(const QPoint &firstPoint, const QPoint &secondPoint);
// ADD-END QMapTracking 2017.11.18 dhthong
};

#endif // QMAPCONTAINER_H
