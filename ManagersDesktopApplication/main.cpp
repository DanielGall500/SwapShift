#include "MenuWindow.h"
#include <QApplication>
#include "Employee/Employee.h"

int main(int argc, char *argv[])
{
    //--TESTING DATABASE--
    Employee x("Daniel Gallagher", 0);
    Employee y("John Gallagher", 1);
    Employee z("Paul Gallagher", 2);

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
