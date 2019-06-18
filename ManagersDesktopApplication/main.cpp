#include "MenuWindow.h"
#include <QApplication>
#include "Employee/Employee.h"
#include <ctime>
#include <cstdlib>

int main(int argc, char *argv[])
{
    srand(time(0));

    //--TESTING DATABASE--
    Employee x("Daniel Gallagher");
    Employee y("John Gallagher");
    Employee z("Paul Gallagher");

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
