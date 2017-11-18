#include "ccDialog.h"
#include "ccDataManager.h"
#include "ccController.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qRegisterMetaType<EventList>("EventList");
    ccDataManager model;
    ccDialog view(model);
    ccController control(model, view);

    view.show();

    return a.exec();
}
