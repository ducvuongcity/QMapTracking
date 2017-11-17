#ifndef COMMON
#define COMMON

#include <QObject>
#include <QThread>
#include <QDebug>
#include <QString>
#include <QRgb>
#include <QtConcurrent/QtConcurrentRun>

#define MACRO_THR_DLOG      qDebug()    << "[" << QThread::currentThreadId() << "][" \
                                        << Q_FUNC_INFO << "]"

#define MACRO_DLOG          qDebug()    << "[" << Q_FUNC_INFO << "]"

#define MACRO_DEL_PTR(ptr)  if(!ptr) { \
                                delete ptr; \
                                ptr = nullptr; \
                            }

#define FILEFORMAT_TFW      QString("tfw")
#define FILEFORMAT_TIF      QString("tif")

#define COLOR_RED           qRgb(255, 0, 0)
#define COLOR_GREEN         qRgb(0,255,0)
#define COLOR_BLUE          qRgb(0, 0, 255)
#define COLOR_YELLOW        qRgb(255, 255, 0)
#define COLOR_BLACK         qRgb(0, 0, 0)
#define COLOR_LINE          COLOR_RED

typedef struct {
    double x;
    double y;
    double z;
    double t;
} ccPoint4D;

typedef struct {
    double A;
    double D;
    double B;
    double E;
    double C;
    double F;
} ccWorldFile;

enum CommonEnum{
    CC_EVT_HMI_READMMS_REQUEST = 0x1000,
    CC_EVT_HMI_READWORLDFILE_REQUEST,

    CC_EVT_MODEL_READMMS_RESPONSE = 0x2000,
    CC_EVT_MODEL_READWORLDFILE_RESPONSE,
    CC_EVT_MODEL_UPDATEPROGRESS_RESPONSE,
};

const QHash <CommonEnum, QString> eventMap = {
    {CC_EVT_HMI_READMMS_REQUEST,                "evt_HMI_ReadMMS_Req"},
    {CC_EVT_HMI_READWORLDFILE_REQUEST,          "evt_HMI_ReadWorldFile_Req"},

    {CC_EVT_MODEL_READMMS_RESPONSE,             "evt_Model_ReadMMS_Res"},
    {CC_EVT_MODEL_READWORLDFILE_RESPONSE,         "evt_Model_ReadWorldFile_Res"},
    {CC_EVT_MODEL_UPDATEPROGRESS_RESPONSE,      "evt_Model_UpdateProgress_Res"}
};
#endif // COMMON

