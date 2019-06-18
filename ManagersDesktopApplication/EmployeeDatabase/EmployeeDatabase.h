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
    ull get_empl_db_indx(string empl_name);
    ull get_empl_db_indx(long empl_id);

	//Check the validity of the roster
	bool valid_roster(Roster r);

public:
    EmployeeDatabase(string db_title);

    //Add, Edit or Delete employees
	void add_employee(Employee empl);
	void del_employee(long empl_ID);

    //TODO: USE ID INSTEAD
    void edit_empl_firstN(string emp_full_name, string new_first_name);
    void edit_empl_lastN(string emp_full_name, string new_last_name);
    void edit_empl_dept(string emp_full_name, string new_dept);


    /*
    void edit_empl_firstN(long ID, string new_first_name);
    void edit_empl_lastN(long ID, string new_last_name);
    void edit_empl_dept(long ID, string new_dept);
    */


    //Get employee information
    string get_empl_firstN(string emp_full_name);
    string get_empl_lastN(string emp_full_name);
    string get_empl_dept(string emp_full_name);

	//Add new roster to the database
	void add_new_roster(Roster r);

    //Get database as vector
    vector<Employee> get_db_vector();


    //TODO: USE ID INSTEAD OF NAME TO FIND EMPLOYEES
    //Find employee in database
    Employee find_employee(string empl_name);

	void print_summary();

};

#endif

