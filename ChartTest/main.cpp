#include "ChartTest.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ChartTest w;
    w.show();
    return a.exec();
}
