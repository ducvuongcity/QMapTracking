#include "ccController.h"

ccController::ccController(ccDataManager &model, ccDialog &view, QObject *parent)
    : QObject(parent)
    , m_model(&model)
    , m_view(&view)
{
    QObject::connect(m_model, SIGNAL(sgnEvent(EventList,QString)), this, SLOT(sltEvenHandle(EventList,QString)));
    QObject::connect(m_view, SIGNAL(sgnEvent(EventList,QString)), this, SLOT(sltEvenHandle(EventList,QString)));
}

void ccController::sltEvenHandle(EventList event, QString params)
{
    QStringList paramList = getEventParameter(params);

//    MACRO_THR_DLOG << "Receive event " << eventName;

    switch (event) {
    case CC_EVT_HMI_READMMS_REQUEST:
        QtConcurrent::run(m_model, m_model->analysisMMS, paramList[0]);
        break;

    case CC_EVT_HMI_READWORLDFILE_REQUEST:
        QtConcurrent::run(m_model, m_model->analysisWorldFile, paramList[0]);
        break;

    case CC_EVT_MODEL_READMMS_RESPONSE:
        if (paramList[0].toInt()) {
            QtConcurrent::run(m_view, &ccDialog::renderMap);
        }

    case CC_EVT_MODEL_READWORLDFILE_RESPONSE:
        if(paramList[0].toInt())
            QtConcurrent::run(m_view, &ccDialog::renderMap);
        break;

    default:
        break;
    }

}

QStringList ccController::getEventParameter(QString params)
{
    return params.split(",");
}
