#include "ccDialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ccDialog dialog;
    dialog.show();

    return a.exec();
}

