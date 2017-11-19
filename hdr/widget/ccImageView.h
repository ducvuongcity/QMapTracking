#ifndef CCIMAGEVIEW_H
#define CCIMAGEVIEW_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsLineItem>
#include <QAction>
#include <QGraphicsView>
#include <QKeyEvent>

class ccImageView : public QGraphicsScene
{
public:
    ccImageView(QObject* parent = 0);


protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
private:
    QPointF origPoint;
    QGraphicsRectItem* rectItemDraw;

public slots:

};

#endif // CCIMAGEVIEW_H
