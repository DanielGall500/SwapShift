#include "MenuWindow.h"
#include <QApplication>
#include "Employee/Employee.h"
#include <ctime>
#include <cstdlib>

int main(int argc, char *argv[])
{
    srand(time(0));

    //--TESTING DATABASE--
    Employee x("Jaime", "Lannister");
    Employee y("Daenarys","Targaeryn");
    Employee z("Tyrion", "Lannister");

    EmployeeDatabase db("Employees");
    db.add_employee(x);
    db.add_employee(y);
    db.add_employee(z);
    //--------------------

    QApplication a(argc, argv);
    MenuWindow w(&db);
    w.show();

    return a.exec();
}
