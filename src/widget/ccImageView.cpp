#include "ccImageView.h"
#include "common.h"


ccImageView::ccImageView(QObject* parent): QGraphicsScene(parent)
{
    rectItemDraw = 0;
}

void ccImageView::mousePressEvent(QGraphicsSceneMouseEvent *event){
    origPoint = event->scenePos();
    QGraphicsScene::mousePressEvent(event);
}

void ccImageView::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
        if(!rectItemDraw){
            rectItemDraw = new QGraphicsRectItem;
            this->addItem(rectItemDraw);
            rectItemDraw->setPen(QPen(Qt::black, 1));
            rectItemDraw->setPos(origPoint);

        }
        rectItemDraw->setRect(0, 0, event->scenePos().x() - origPoint.x(),
                              event->scenePos().y() - origPoint.y());
}

void ccImageView::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){

    removeItem(rectItemDraw);
    rectItemDraw = 0;
    this->addLine(100, 100, 200, 200, QPen(Qt::blue, 5));
    QGraphicsScene::mouseReleaseEvent(event);
}

void ccImageView::keyPressEvent(QKeyEvent *event){
    if(event->key() == Qt::Key_Delete)
        foreach(QGraphicsItem* item, selectedItems()){
            removeItem(item);
            delete item;
        }
    else
        QGraphicsScene::keyPressEvent(event);
}
