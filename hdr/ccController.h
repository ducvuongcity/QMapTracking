#ifndef CCCONTROLLER_H
#define CCCONTROLLER_H

#include <QObject>

#include "common.h"
#include "ccDataManager.h"
#include "ccDialog.h"

class ccController : public QObject
{
    Q_OBJECT
public:
    explicit ccController(ccDataManager &model, ccDialog &view, QObject *parent = 0);
    QStringList getEventParameter(QString params);

signals:

public slots:
    void sltEvenHandle(EventList event, QString params);

private:
    ccDataManager *m_model;
    ccDialog *m_view;

};

#endif // CCCONTROLLER_H
