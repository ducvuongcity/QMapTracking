#ifndef COMMON
#define COMMON

#include <QObject>
#include <QThread>
#include <QDebug>
#include <QString>
#include <QRgb>
#include <QtConcurrent/QtConcurrentRun>

#include "ccBridge.h"
#include "ccDataStore.h"

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
    CC_TYPE_MMS = 0x00,
    CC_TYPE_WORLDFILE,

    CC_REQUEST_RENDER_MAP = 0x10,

};

#endif // COMMON

