#include "filerenamer.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FileRenamer w;
    w.show();

    return a.exec();
}
