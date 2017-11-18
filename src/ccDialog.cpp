#include "ccDialog.h"

ccDialog::ccDialog(QWidget *parent)
    : QDialog(parent)
{
    qRegisterMetaType<EventList>("EventList");
    model = new ccDataManager;
    view = new ccMapWidget(model);
    control = new ccController(model, view);

    setWindowTitle("Map Tracking");
    setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, QSize(640, 800), qApp->desktop()->availableGeometry()));
    verticalLayout = new QVBoxLayout(this);
    verticalLayout->addWidget(view);
}

ccDialog::~ccDialog()
{}
