#include "ccController.h"

ccController::ccController(ccBridge &bridge, ccDataManager &model, ccDialog &view, QObject *parent)
    : QObject(parent)
    , m_bridge(bridge)
    , m_model(model)
    , m_view(view)
{
    connect(m_bridge, SIGNAL(sgnEventToController(QString)), this, SLOT(sltEvenHandle(QString)));
}

void ccController::sltEvenHandle(QString event)
{
    QList<QVariant> params;
    QString eventName;
}

