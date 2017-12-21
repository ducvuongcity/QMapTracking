#include "ccDialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ccDialog dialog;
    dialog.setFixedWidth(640);
    dialog.setFixedHeight(800);
    dialog.show();

    return a.exec();
}
