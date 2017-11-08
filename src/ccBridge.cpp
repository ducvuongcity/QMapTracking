#include "ccBridge.h"

ccBridge::ccBridge(QObject *parent) : QObject(parent)
{}

void ccBridge::sendEventToController(QString send, QString event)
{
    emit sgnEventToController(event);
}

void ccBridge::sendEventToModel(QString send, QString event)
{
    emit sgnEventToModel(event);
}

void ccBridge::sendEventToView(QString send, QString event)
{
    emit sgnEventToView((event));
}

