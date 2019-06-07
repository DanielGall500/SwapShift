#include "EmployeeDatabase.h"

EmployeeDatabase::EmployeeDatabase(string title) :
	db_title(title)
{

}

void EmployeeDatabase::add_employee(Employee empl)
{
	empl_db.push_back(empl);
}

void EmployeeDatabase::del_employee(long empl_ID)
{
	bool success = false;
	int indx = 0;
	long tmp_ID;

	//Iterate employees in database
	for (Employee &i : empl_db)
	{
		tmp_ID = i.get_employee_ID();

		//Deletion based on ID number
		if (tmp_ID == empl_ID)
		{
			empl_db.erase(empl_db.begin() + indx);
			success = true;
			break;
		}

		indx++;
	}

	if(!success)
		cout << "Employee Not Found" << endl;
	
}
