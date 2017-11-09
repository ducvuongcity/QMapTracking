#ifndef CCCONTROLLER_H
#define CCCONTROLLER_H

#include <QObject>

#include "common.h"
#include "ccDataManager.h"
#include "ccDialog.h"
#include "ccBridge.h"

class ccController : public QObject
{
    Q_OBJECT
public:
    explicit ccController(ccBridge &bridge, ccDataManager &model, ccDialog &view, QObject *parent = 0);

signals:

public slots:
    void sltEvenHandle(QString event);

private:
    QStringList getEventParameter(QString eventWithParam, QString &eventName);

private:
    ccBridge *m_bridge;
    ccDataManager *m_model;
    ccDialog *m_view;

};

#endif // CCCONTROLLER_H
