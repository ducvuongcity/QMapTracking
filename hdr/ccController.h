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
    explicit ccController(ccDataManager &model, ccDialog &view, ccBridge &bridge, QObject *parent = 0);

signals:

public slots:
    void sltEvenHandle(QString event);

private:
    ccBridge *m_bridge;
    ccDataManager *m_model;
    ccDialog *m_view;

};

#endif // CCCONTROLLER_H
