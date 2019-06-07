#ifndef __SwapShiftEmployeeDatabase__
#define __SwapShiftEmployeeDatabase__

#include "Employee\Employee.h"
#include <vector>
#include <iostream>

class EmployeeDatabase
{
	string db_title;

	vector<Employee> empl_db;

public:
	EmployeeDatabase(string db_title);

	void add_employee(Employee empl);
	void del_employee(long empl_ID);

	vector<Employee> get_database() { return empl_db; }



};

#endif __SwapShiftEmployeeDatabase__

