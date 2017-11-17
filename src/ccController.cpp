#include "ccController.h"

ccController::ccController(ccDataManager &model, ccDialog &view, QObject *parent)
    : QObject(parent)
    , m_model(&model)
    , m_view(&view)
{
    QObject::connect(m_model, SIGNAL(sgnEvent(QString)), this, SLOT(sltEvenHandle(QString)));
    QObject::connect(m_view, SIGNAL(sgnEvent(QString)), this, SLOT(sltEvenHandle(QString)));
}

void ccController::sltEvenHandle(QString event)
{
    QStringList params;
    QString eventName;
    params = getEventParameter(event, eventName);

    MACRO_THR_DLOG << "Receive event " << eventName;

    switch (eventMap.key(eventName)) {
    case CC_EVT_HMI_READMMS_REQUEST:
        QtConcurrent::run(m_model, m_model->analysisMMS, params[0]);
        break;

    case CC_EVT_HMI_READWORLDFILE_REQUEST:
        QtConcurrent::run(m_model, m_model->analysisWorldFile, params[0]);
        break;

    case CC_EVT_MODEL_READMMS_RESPONSE:
        if (params[0].toInt()) {
            QtConcurrent::run(m_view, &ccDialog::renderMap);
        }

    case CC_EVT_MODEL_READWORLDFILE_RESPONSE:
        if(params[0].toInt())
            QtConcurrent::run(m_view, &ccDialog::renderMap);
        break;

    default:
        break;
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
