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

enum EMPL_VAR {NAME, ID};

class EmployeeDatabase
{
	string db_title;

    vector<Employee> empl_db;

    //General information about the uploaded rosters
    vector<roster_info> r_info;

    //SQL
    QSqlDatabase *empl_sql_db;
    QSqlQueryModel *sql_model;
    QSqlQuery *query;


	/* Find the location of the employee in the database
	Input either the name or ID as the information we can use
	to search for this employee.
	The unique ID is safer, however sometimes we only have the name.
	*/
    size_t get_empl_db_indx(string empl_info, EMPL_VAR search_type);

public:
    EmployeeDatabase(QSqlDatabase *empl_db, string db_title);

    //Add, Edit or Delete employees
	void add_employee(Employee empl);
    void del_employee(string empl_ID);

    void edit_empl_firstN(string ID, string new_first_name);
    void edit_empl_lastN(string ID, string new_last_name);
    void edit_empl_dept(string ID, string new_dept);

    //Get employee information
    string get_empl_firstN(string ID);
    string get_empl_lastN(string ID);
    string get_empl_dept(string ID);

	//Used to prevent two employee's of the same name
    bool empl_exists(string fsize_t_name);

	//Add new roster to the database
    void add_new_roster(Roster& r);

    //Get database as vector
    vector<Employee> get_db_vector();

    //Find employee in database
    Employee find_employee(string empl_unique_ID);

    //Get Employee Names
    vectorStr get_empl_names();

    //Get Roster Titles & Dates
    vectorStr get_roster_titles();
    vectorStr2D get_roster_dates();

    roster_info get_roster_info(string title);

    bool has_shift(string name, string date, string roster, shift &return_shift);

    map<string, Employee> create_empl_map();

    void print_summary();
};

#endif

