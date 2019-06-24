#include "EmployeeDatabase.h"
#include "Roster/Roster.h"

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
ull EmployeeDatabase::get_empl_db_indx(string empl_info, EMPL_VAR search_type)
{
    ull indx = 0;

	for (Employee& e : empl_db)
	{
		/*  We can search for employees based on ID
			or name. curr_info changes the info we look for
			from the current iterated employee based on the search 
			type we're carrying out. */
		string curr_info = search_type == NAME ? e.get_full_name() : e.get_unique_ID();

        if (curr_info == empl_info)
			break;

		indx++;
	}

	return indx;
}

Employee EmployeeDatabase::find_employee(string empl_ID)
{
    ull indx = get_empl_db_indx(empl_ID, ID);
    return empl_db[indx];
}

//Edit Employees
void EmployeeDatabase::edit_empl_firstN(string empl_ID, string new_first_name)
{
    ull emp_indx = get_empl_db_indx(empl_ID, ID);

    empl_db[emp_indx].set_first_name(new_first_name);

}

void EmployeeDatabase::edit_empl_lastN(string empl_ID, string new_last_name)
{
    ull emp_indx = get_empl_db_indx(empl_ID, ID);

    empl_db[emp_indx].set_last_name(new_last_name);
}

void EmployeeDatabase::edit_empl_dept(string empl_ID, string new_dept)
{
    ull emp_indx = get_empl_db_indx(empl_ID, ID);

    empl_db[emp_indx].set_department(new_dept);
}

//Get employee info
string EmployeeDatabase::get_empl_firstN(string empl_ID)
{
    ull emp_indx = get_empl_db_indx(empl_ID, ID);
    return empl_db[emp_indx].get_first_name();
}

string EmployeeDatabase::get_empl_lastN(string empl_ID)
{
    ull emp_indx = get_empl_db_indx(empl_ID, ID);
    return empl_db[emp_indx].get_last_name();
}

string EmployeeDatabase::get_empl_dept(string empl_ID)
{
    ull emp_indx = get_empl_db_indx(empl_ID, ID);
    return empl_db[emp_indx].get_department();
}

//Roster Functions
void EmployeeDatabase::add_new_roster(Roster r)
{
    //Declare variables
    map<string, vector<shift>> empl_shift_map = r.get_empl_shifts();
    vector<string> dates = r.get_shift_dates();
    vector<shift> shifts;

    string name;
    ull empl_db_indx;

    for (auto &it : empl_shift_map)
    {
        //Name of employee is the map key
        name = it.first;

        //Vector of the shifts as the value
        shifts = it.second;

		//Ensure employee exists in the database
		if (empl_exists(name))
		{
			/* We only have access to the employee's name.
		       Therefore, we have to search using the name
		       instead of ID. */
			empl_db_indx = get_empl_db_indx(name, NAME);


			/*Iterate through each shift the employee
              has on this roster. We give each shift to 
              the employee as we iterate through them */
			for (auto& s : shifts)
				empl_db[empl_db_indx].set_shift(s);
        }
    }

    //Add roster title to list
    roster_titles.push_back(r.get_title());
}

//Other Functions
void EmployeeDatabase::print_summary()
{
    cout << "--START SUMMARY--"
         << endl << endl;

    for (Employee& e : empl_db)
    {
        string name = e.get_full_name();
        string id = e.get_unique_ID();
        vector<shift> shifts = e.get_all_shifts();

        cout << "--EMPLOYEE--" << endl;
        cout << "Name: " << name << endl;

        for(shift &s : shifts)
        {
            cout << "Shift " << s.str_date
                 << " @" << s.start_time
                 << "-" << s.end_time
                 << endl;
        }

        cout << endl << endl;

    }
    cout << "--END SUMMARY--" << endl << endl;
}

vector<Employee> EmployeeDatabase::get_db_vector()
{
    return empl_db;
}

bool EmployeeDatabase::empl_exists(string full_name)
{
	for (Employee& e : empl_db)
	{
		if (e.get_full_name() == full_name)
			return true;
	}

	return false;
}

vectorStr EmployeeDatabase::get_empl_names()
{
    vectorStr empl_list;

    for(Employee e : empl_db)
        empl_list.push_back(e.get_full_name());

    return empl_list;
}

vectorStr EmployeeDatabase::get_roster_titles()
{
    return roster_titles;
}





















