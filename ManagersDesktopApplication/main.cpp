#include "MenuWindow.h"
#include <QApplication>
#include "Employee/Employee.h"
#include <ctime>
#include <cstdlib>
#include <QtSql>
#include <fstream>

int main(int argc, char *argv[])
{
    srand(time(0));

    //--SQL--
    //RETRIEVE DATABASE PASSWORD
    ifstream fPASS;
    string DB_PASS;

    fPASS.open("C:\\Users\\DannyG\\Desktop\\Projects\\Files\\DB_PASS.txt");

    if(fPASS.good())
        getline(fPASS, DB_PASS);
    else
        qDebug() << "Cannot Open DB_PASS File";
   //---------------------------


    //Connect to SQL Database

    //Create DB connection
    QSqlDatabase sql_db = QSqlDatabase::addDatabase("QMYSQL");

    sql_db.setDatabaseName("swapshift_db");
    sql_db.setHostName("127.0.0.1");
    sql_db.setUserName("root");
    sql_db.setPassword(QString::fromStdString(DB_PASS));

    //Open DB
    if(sql_db.open())
        qDebug() << "Success";
    else
    {
        qDebug() << sql_db.lastError();
    }




    //--TESTING DATABASE--

    EmployeeDatabase db(&sql_db, "Employees");
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
