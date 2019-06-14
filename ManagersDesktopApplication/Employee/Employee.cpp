//
//  Employee.cpp
//  SwapShiftEmployeeClass
//
//  Created by Daniel Gallagher on 04/06/2019.
//  Copyright (c) 2019 Developer Co. All rights reserved.
//

#include "Employee.h"


//Constructor
Employee::Employee(string full_name, long empl_id) :
	empl_full_name(full_name), empl_ID(empl_id)
{
	//Set first name 
	empl_first_name = full_name.substr(0, full_name.find(" "));

	//Set last name
	empl_last_name = full_name.substr(full_name.find(" ") + 1);
}

//First Name
string Employee::get_first_name() { return empl_first_name; }
void   Employee::set_first_name(string f) { empl_first_name = f; }

//Last Name
string Employee::get_last_name() { return empl_last_name; };
void   Employee::set_last_name(string l) { empl_last_name = l; }

//Full Name
string Employee::get_full_name() { return empl_full_name; };

//Department
string Employee::get_department() { return empl_department; };
void   Employee::set_department(string d) { empl_department = d; }

//Shifts
void Employee::set_shift(shift s)
{
    empl_shifts[s.str_date] = s;
}

shift Employee::get_shift(string d)
{
    return empl_shifts[d];
}

void Employee::del_shift(string d)
{
    empl_shifts.erase(d);
}

//Print Functions
void Employee::print_shifts()
{
	for (auto &it : empl_shifts)
	{
		string date = it.first;
		shift s = it.second;
		
		cout << "Date: " << date << endl;

		cout << "Shift: " << s.start_time <<
			" - " << s.end_time << endl;
	}
}

//Non-Class Functions

void swap_shift(Employee& A, string A_date, Employee& B, string B_date) //A and Bs original shifts
{
    //Create a temporary variable to hold the shift of the employees
    shift A_temp = A.get_shift(A_date);
    shift B_temp = B.get_shift(B_date);
    
    //Delete shift A and B
    A.del_shift(A_date);
    B.del_shift(B_date);
    
    //Swap the shifts
    A.set_shift(B_temp);
    B.set_shift(A_temp);
    
} 
