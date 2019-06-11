#ifndef __SwapShiftEmployeeDatabase__
#define __SwapShiftEmployeeDatabase__

#include "Employee\Employee.h"
#include "Roster\Roster.h"
#include <vector>
#include <iostream>

class EmployeeDatabase
{
	string db_title;

	vector<Employee> empl_db;

	//The location of the employee in the database
	int get_empl_db_indx(string empl_name);
	int get_empl_db_indx(long empl_id);

	//Check the validity of the roster
	bool valid_roster(Roster r);

public:
	EmployeeDatabase(string db_title);

	void add_employee(Employee empl);
	void del_employee(long empl_ID);

	vector<Employee> get_database() { return empl_db; }

	void add_new_roster(Roster r);



};

#endif __SwapShiftEmployeeDatabase__

