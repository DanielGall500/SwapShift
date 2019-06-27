#include "MenuWindow.h"
#include <QApplication>
#include "Employee/Employee.h"
#include <ctime>
#include <cstdlib>

int main(int argc, char *argv[])
{
    srand(time(0));

    //--TESTING DATABASE--
    Employee s("Jimmy", "Neutron");
    Employee x("Daniel", "Gallagher");
    Employee y("Jack","Sweeney");
    Employee z("Nathan", "Doyle");

    EmployeeDatabase db("Employees");
    db.add_employee(s);
    db.add_employee(x);
    db.add_employee(y);
    db.add_employee(z);
    //--------------------

    //Add Base Roster
    vectorStr ignore{"Department"}; //ignores these lines completely
    CSVReader csv("C:\\Users\\DannyG\\Desktop\\Projects\\Files\\BasicRoster.csv", ignore);
    vectorStr2D csv_vec;
    row_pos dates_pos(0, 1);
    col_pos names_pos(0, 1);

    if(csv.open_file())
        csv_vec = csv.read_csv();

    vectorStr non_shifts{"N/A", "Hol"};
    Roster r("Week1", csv_vec, names_pos, dates_pos,non_shifts);
    db.add_new_roster(r);

    //Run Application
    QApplication a(argc, argv);
    MenuWindow w(&db);
    w.show();

    return a.exec();
}
