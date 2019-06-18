#include "EmployeeDatabase.h"

EmployeeDatabase::EmployeeDatabase(string title) :
	db_title(title)
{}

void EmployeeDatabase::add_employee(Employee empl)
{
	empl_db.push_back(empl);
}

void EmployeeDatabase::del_employee(string empl_ID)
{
	bool success = false;
	int indx = 0;
    string tmp_ID;

	//Iterate employees in database
	for (Employee &i : empl_db)
	{
        tmp_ID = i.get_unique_ID();

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
ull EmployeeDatabase::get_empl_db_indx(string empl_id)
{
    ull indx = 0;

	for (Employee& e : empl_db)
	{
        if (e.get_unique_ID() == empl_id)
			break;

		indx++;
	}

	return indx;
}

Employee EmployeeDatabase::find_employee(string ID)
{
    ull indx = get_empl_db_indx(ID);
    return empl_db[indx];
}

//ADD CHECKS
bool EmployeeDatabase::valid_roster(Roster r)
{

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
    ull empl_db_indx;

	//TODO: HANDLE IF THERES A NAME THATS NOT IN DATABASE
	for (auto &it : empl_shift_map)
	{
		//Name of employee is the map key
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
        string id = e.get_unique_ID();

		cout << "Name: " << name << endl;
		cout << "Unique ID: " << id << endl;
		e.print_shifts();

	}
}

vector<Employee> EmployeeDatabase::get_db_vector()
{
    return empl_db;
}

//Edit Employees
void EmployeeDatabase::edit_empl_firstN(string ID, string new_first_name)
{
    ull emp_indx = get_empl_db_indx(ID);

    empl_db[emp_indx].set_first_name(new_first_name);

}

void EmployeeDatabase::edit_empl_lastN(string ID, string new_last_name)
{
    ull emp_indx = get_empl_db_indx(ID);

    empl_db[emp_indx].set_last_name(new_last_name);
}

void EmployeeDatabase::edit_empl_dept(string ID, string new_dept)
{
    ull emp_indx = get_empl_db_indx(ID);

    empl_db[emp_indx].set_department(new_dept);
}

//Get employee info
string EmployeeDatabase::get_empl_firstN(string ID)
{
    ull emp_indx = get_empl_db_indx(ID);
    return empl_db[emp_indx].get_first_name();
}

string EmployeeDatabase::get_empl_lastN(string ID)
{
    ull emp_indx = get_empl_db_indx(ID);
    return empl_db[emp_indx].get_last_name();
}

string EmployeeDatabase::get_empl_dept(string ID)
{
    ull emp_indx = get_empl_db_indx(ID);
    return empl_db[emp_indx].get_department();
}























