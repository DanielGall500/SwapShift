#include "menuwindow.h"
#include <QApplication>
#include "Employee/Employee.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MenuWindow w;

    w.setStyleSheet("background-color: rgb(35, 200, 255)");
    w.show();

    return a.exec();
}
