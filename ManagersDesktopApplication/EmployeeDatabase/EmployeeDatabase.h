#ifndef EMPLOYEE_DATABASE
#define EMPLOYEE_DATABASE

#include "Employee/Employee.h"
#include "globals.h"
#include "Structs.h"
#include <vector>
#include <iostream>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>
#include <iostream>
#include <QDebug>
#include <QSqlError>

class Roster;

class EmployeeDatabase
{
	string db_title;

    vector<Employee> empl_db;

    //General information about the uploaded rosters
    vector<roster_info> r_info;

    //SQL (declared in constructor)
    QSqlDatabase *empl_sql_db;
    QSqlQueryModel *sql_model;
    QSqlQuery *query;

    QString query_edit_empl_info(int empl_ID, string col_name, string new_val);
    QString query_get_empl_info(int empl_ID, string col_name);


    //Unsafe
   // size_t get_empl_db_indx(string f_name, string l_name);

    //Safe
   // size_t get_empl_db_indx(int ID);

public:
    EmployeeDatabase(QSqlDatabase *empl_db, string db_title);


    //Add, Edit or Delete employees
    void add_employee(Employee empl); //sql
    void del_employee(int empl_ID); //sql

    void edit_empl_firstN(int ID, string new_first_name); //sql
    void edit_empl_lastN(int ID, string new_last_name); //sql
    void edit_empl_dept(int ID, string new_dept); //sql

    //Get employee information
    string get_empl_firstN(int ID); //sql
    string get_empl_lastN(int ID);  //sql
    string get_empl_dept(int ID);  //sql
    int    get_empl_id(string f_name, string l_name);

	//Used to prevent two employee's of the same name
    bool empl_exists(string first_name, string last_name); //sql

	//Add new roster to the database
    void add_new_roster(Roster& r); //sql

    //Get database as vector
    vector<Employee> get_db_vector(); //sql

    //Find employee in database
    Employee find_employee(int empl_ID); //sql

    //Get Employee Names
    vectorStr get_empl_names(); //works w sql

    //Get Roster Titles & Dates
    vectorStr get_roster_titles();
    vectorStr2D get_roster_dates();

    roster_info get_roster_info(string title);

    bool has_shift(int empl_id, string date, string roster, shift &return_shift); //sql

    map<string, Employee> create_empl_map();

    void print_summary();
};

#endif

