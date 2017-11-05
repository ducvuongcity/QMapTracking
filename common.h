#ifndef COMMON
#define COMMON

#include <QObject>
#include <QThread>
#include <QDebug>
#include <QString>

#define MACRO_THREAD_DLOG qDebug() << "[" << QThread::currentThreadId() << "] "

typedef struct {
    double x;
    double y;
    double z;
    double t;
} ccPoint4D;

#endif // COMMON

