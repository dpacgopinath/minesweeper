#include <QtGui/QApplication>
#include "minesweeper.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    minesweeper w;
    w.show();

    return a.exec();
}

