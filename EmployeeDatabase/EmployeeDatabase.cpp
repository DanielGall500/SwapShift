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

//ID safer than name
int EmployeeDatabase::get_empl_db_indx(long empl_id)
{
	int indx = 0;

	for (Employee& e : empl_db)
	{
		if (e.get_employee_ID() == empl_id)
			break;

		indx++;
	}

	return indx;
}

int EmployeeDatabase::get_empl_db_indx(string empl_name)
{
	int indx = 0;

	for (Employee& e : empl_db)
	{
		if (e.get_full_name() == empl_name)
			break;

		indx++;
	}

	return indx;
}

bool EmployeeDatabase::valid_roster(Roster r)
{
	cout << r.get_empl_shifts().size() << endl;
	cout << r.get_shift_dates().size() << endl;
	cout << "yy " << endl;

	for (auto& i : r.get_empl_shifts())
	{
		cout << i.first << endl;
	}

	//Check 1: Same amount of shifts as shift dates
	if (r.get_empl_shifts().size() != r.get_shift_dates().size())
		return false;

	return true;
}

void EmployeeDatabase::add_new_roster(Roster r)
{
	//Ensure roster is correct format
	if (!valid_roster(r))
	{
		cout << "Roster Invalid" << endl;
		getchar();
		exit(1);
	}

	//Declare variables
	map<string, vector<shift>> empl_shift_map = r.get_empl_shifts();
	vector<string> dates = r.get_shift_dates();
	vector<shift> shifts;

	string name;
	int empl_db_indx;

	//TODO: HANDLE IF THERES A NAME THATS NOT IN DATABASE
	for (auto &it : empl_shift_map)
	{
		//Name of employee is the key
		name = it.first;

		//Vector of the shifts as the value
		shifts = it.second;

		//Find employee's location in database
		empl_db_indx = get_empl_db_indx(name);


		//Give the shifts to the employees
		for (auto& s : shifts)
			empl_db[empl_db_indx].set_shift(s);
	}
}

void EmployeeDatabase::print_summary()
{
	for (Employee& e : empl_db)
	{
		string name = e.get_full_name();
		long id = e.get_employee_ID();

		cout << "Name: " << name << endl;
		cout << "Unique ID: " << id << endl;
		e.print_shifts();

	}
}
