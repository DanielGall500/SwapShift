#ifndef EMPLOYEE_DATABASE
#define EMPLOYEE_DATABASE

#include "Employee\Employee.h"
#include "Roster\Roster.h"
#include <vector>
#include <iostream>

typedef unsigned long long ull;

class EmployeeDatabase
{
	string db_title;

	vector<Employee> empl_db;

	//The location of the employee in the database
    ull get_empl_db_indx(string empl_unique_ID);

	//Check the validity of the roster
	bool valid_roster(Roster r);

public:
    EmployeeDatabase(string db_title);

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

	//Add new roster to the database
	void add_new_roster(Roster r);

    //Get database as vector
    vector<Employee> get_db_vector();


    //TODO: USE ID INSTEAD OF NAME TO FIND EMPLOYEES
    //Find employee in database
    Employee find_employee(string empl_unique_ID);

	void print_summary();

};

#endif

