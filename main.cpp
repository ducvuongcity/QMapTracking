#include "ccDialog.h"
#include "ccController.h"
#include "ccBridge.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ccBridge bridge;
    ccDataStore store;
    ccDialog view(bridge, store);
    ccDataManager model(bridge, store);
    ccController controller(bridge, model, view);

    view.show();

    return a.exec();
}
