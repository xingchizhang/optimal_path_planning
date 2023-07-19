#include "optimal_path_planning.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    optimal_path_planning w;
    w.show();
    return a.exec();
}
