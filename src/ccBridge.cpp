#include "ccBridge.h"

ccBridge::ccBridge(QObject *parent) : QObject(parent)
{}

void ccBridge::sendEventToController(QString event)
{
    emit sgnEventToController(event);
}

void ccBridge::sendEventToModel(QString event)
{
    emit sgnEventToModel(event);
}

void ccBridge::sendEventToView(QString event)
{
    emit sgnEventToView((event));
}

