#include "MenuWindow.h"
#include <QApplication>
#include "Employee/Employee.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MenuWindow w;
    w.show();

    return a.exec();
}
