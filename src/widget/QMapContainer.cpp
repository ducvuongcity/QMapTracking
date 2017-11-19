#include "QMapContainer.h"


QMapContainer::QMapContainer(QWidget *parent, Qt::WindowFlags f)
    : QLabel(parent, f)
{
    m_pRubberBand = nullptr;
}

void QMapContainer::mousePressEvent(QMouseEvent *ev)
{
//    QToolTip::showText(ev->globalPos(), QString("%1, %2").arg(ev->x()).arg(ev->y()));
    emit sgnMousePressEvent(ev->globalPos(), ev->pos());
// ADD-START QMapTracking 2017.11.18 dhthong
    createRubberBand(ev);
// ADD-END QMapTracking 2017.11.18 dhthong
}
// ADD-START QMapTracking 2017.11.18 dhthong
void QMapContainer::createRubberBand(QMouseEvent *ev)
{
    m_firstPoint = ev->pos();
    if(nullptr == m_pRubberBand)
    {
        m_pRubberBand = new QRubberBand(QRubberBand::Rectangle, this);
    }
    m_pRubberBand->setGeometry(QRect(m_firstPoint, QSize()));
    m_pRubberBand->show();
}

void QMapContainer::mouseMoveEvent(QMouseEvent *ev)
{
    if(nullptr == m_pRubberBand)
    {
        return;
    }
    QPoint currentPoint(ev->pos());
    // check if the size of the rectangle is valid
    int width = currentPoint.x() - m_firstPoint.x();
    int height = currentPoint.y() - m_firstPoint.y();
    long size = width * width + height * height;
    if( (CC_SELECT_SIZE * CC_SELECT_SIZE) < size )
    {
        double aspec = CC_SELECT_SIZE / qSqrt(size);
        int newXAxis = (int)(aspec * width) + m_firstPoint.x();
        int newYAxis = (int)(aspec * height) + m_firstPoint.y();
        QPoint newPoint(newXAxis, newYAxis);
        m_pRubberBand->setGeometry(QRect(m_firstPoint, newPoint).normalized());
    }
    else
    {
        m_pRubberBand->setGeometry(QRect(m_firstPoint, ev->pos()).normalized());
    }
}

void QMapContainer::mouseReleaseEvent(QMouseEvent *ev)
{
    if(nullptr != m_pRubberBand)
    {
        m_pRubberBand->hide();
        emit sgnmouseReleaseEvent(m_firstPoint, ev->pos());
        delete m_pRubberBand;
        m_pRubberBand = nullptr;
    }
}

QMapContainer::~QMapContainer()
{
    MACRO_DEL_PTR(m_pRubberBand);
}
// ADD-END QMapTracking 2017.11.18 dhthong
