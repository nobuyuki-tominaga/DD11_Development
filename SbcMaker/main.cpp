#include "SbcMakerMainWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CSbcMakerMain w;
    w.show();

    return a.exec();
}
