#ifndef CCDIALOG_H
#define CCDIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include "common.h"
#include "ccController.h"
#include "ccDataManager.h"
#include "ccMapWidget.h"

class ccDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ccDialog(QWidget *parent = 0);
    ~ccDialog();
    QVBoxLayout *verticalLayout;

    ccDataManager *model;
    ccMapWidget *view;
    ccController *control;
};

#endif // CCDIALOG_H
