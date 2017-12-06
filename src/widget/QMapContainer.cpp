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
    int32_t width = currentPoint.x() - m_firstPoint.x();
    int32_t height = currentPoint.y() - m_firstPoint.y();
    uint64_t size = width * width + height * height;
    if( (CC_SELECT_SIZE * CC_SELECT_SIZE) < size )
    {
        double aspec = CC_SELECT_SIZE / qSqrt(size);
        int32_t newXAxis = (int32_t)(aspec * width) + m_firstPoint.x();
        int32_t newYAxis = (int32_t)(aspec * height) + m_firstPoint.y();
        m_secondPoint.setX(newXAxis);
        m_secondPoint.setY(newYAxis);
        m_pRubberBand->setGeometry(QRect(m_firstPoint, m_secondPoint).normalized());
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
        emit sgnmouseReleaseEvent(m_firstPoint, m_secondPoint);
        delete m_pRubberBand;
        m_pRubberBand = nullptr;
    }
}

QMapContainer::~QMapContainer()
{
    MACRO_DEL_PTR(m_pRubberBand);
}
// ADD-END QMapTracking 2017.11.18 dhthong
