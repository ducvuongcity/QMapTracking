#ifndef CCQLABEL_H
#define CCQLABEL_H

#include <QLabel>
#include <QMouseEvent>
#include <QToolTip>
#include <QRubberBand>
#include <QtMath>
#include "common.h"

class ccQLabel : public QLabel
{
    Q_OBJECT

private:
    bool m_usingRubberBand = false;
    QRubberBand *m_pRubberBand;
    QPoint m_firstPoint;
    QPoint m_secondPoint;

    void createRubberBand(QMouseEvent *ev);

public:
    explicit ccQLabel(QWidget* parent = 0, Qt::WindowFlags f = 0, bool rubberBand = false);
    void mousePressEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);
    virtual ~ccQLabel();

signals:
    void sgnMousePressEvent(const QPoint &globalPoint, const QPoint &localPoint);
    void sgnmouseReleaseEvent(const QPoint &firstPoint, const QPoint &secondPoint);
};

#endif // CCQLABEL_H
