#include "ccController.h"

ccController::ccController(ccBridge &bridge, ccDataManager &model, ccDialog &view, QObject *parent)
    : QObject(parent)
    , m_bridge(&bridge)
    , m_model(&model)
    , m_view(&view)
{
    connect(m_bridge, SIGNAL(sgnEventToController(QString)), this, SLOT(sltEvenHandle(QString)));
}

void ccController::sltEvenHandle(QString event)
{
    QStringList params;
    QString eventName;
    params = getEventParameter(event, eventName);

    if(eventName == "evt_View_LoadMMS_Req") {
        QtConcurrent::run(m_model, m_model->analysisMMS, params[0]);
    }
    else if (eventName == "") {

    }
    else if (eventName == "") {

    }
}

QStringList ccController::getEventParameter(QString eventWithParam, QString &eventName)
{
    uint8_t startIndexParam = eventWithParam.indexOf("(");
    uint8_t endIndexParam = eventWithParam.indexOf(")");
    QString paramsString = eventWithParam.mid(startIndexParam + 1, endIndexParam - startIndexParam - 1);
    eventName = eventWithParam.mid(0, startIndexParam);

    MACRO_THR_DLOG << "eventName = " << eventName << ", paramsString = " << paramsString;

    return paramsString.split(",");
}

