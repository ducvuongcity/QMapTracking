#include "ccQLabel.h"


ccQLabel::ccQLabel(QWidget *parent, Qt::WindowFlags f, bool rubberBand)
    : QLabel(parent, f)
    , m_usingRubberBand(rubberBand)
{
    MACRO_THR_DLOG << "m_usingRubberBand: " << m_usingRubberBand;
    m_pRubberBand = nullptr;
}

void ccQLabel::mousePressEvent(QMouseEvent *ev)
{
//    QToolTip::showText(ev->globalPos(), QString("%1, %2").arg(ev->x()).arg(ev->y()));
    MACRO_THR_DLOG << "START ";
    emit sgnMousePressEvent(ev->globalPos(), ev->pos());
    if (m_usingRubberBand) {
        createRubberBand(ev);
    }
    MACRO_THR_DLOG << "END ";
}

void ccQLabel::createRubberBand(QMouseEvent *ev)
{
    if(m_usingRubberBand) {
        m_firstPoint = ev->pos();
        m_secondPoint = m_firstPoint;
        if(nullptr == m_pRubberBand)
        {
            m_pRubberBand = new QRubberBand(QRubberBand::Rectangle, this);
        }
        m_pRubberBand->setGeometry(QRect(m_firstPoint, QSize()));
        m_pRubberBand->show();
    }
}

void ccQLabel::mouseMoveEvent(QMouseEvent *ev)
{
    MACRO_THR_DLOG << "START ";
    if(m_usingRubberBand) {
        if(nullptr == m_pRubberBand)
        {
            return;
        }
        QPoint currentPoint(ev->pos());
        // check if the size of the rectangle is valid
        int32_t width = currentPoint.x() - m_firstPoint.x();
        int32_t height = currentPoint.y() - m_firstPoint.y();
        uint64_t size = width * width + height * height;
        if(0 == size)
        {
            return;
        }
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
            m_secondPoint = ev->pos();
            m_pRubberBand->setGeometry(QRect(m_firstPoint, ev->pos()).normalized());
        }
    }
    MACRO_THR_DLOG << "END";
}

void ccQLabel::mouseReleaseEvent(QMouseEvent *ev)
{
    MACRO_THR_DLOG << "START ";
    if(m_usingRubberBand) {
        if(nullptr != m_pRubberBand)
        {
            m_pRubberBand->hide();
            emit sgnmouseReleaseEvent(m_firstPoint, m_secondPoint);
            MACRO_THR_DLOG << "delete RubbleBand";
            delete m_pRubberBand;
            m_pRubberBand = nullptr;
            m_firstPoint = m_secondPoint;
        }
    }
    MACRO_THR_DLOG << "END";
}

ccQLabel::~ccQLabel()
{
    MACRO_DEL_PTR(m_pRubberBand);
}
