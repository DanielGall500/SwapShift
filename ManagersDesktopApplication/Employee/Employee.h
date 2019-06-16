//
//  Employee.h
//  SwapShiftEmployeeClass
//
//  Created by Daniel Gallagher on 04/06/2019.
//  Copyright (c) 2019 Developer Co. All rights reserved.
//

#ifndef __SwapShiftEmployeeClass__Employee__
#define __SwapShiftEmployeeClass__Employee__

#include <string>
#include <iostream>
#include <map>
#include "Structs.h"

using namespace std;

class Employee
{
    
    string empl_first_name, empl_last_name, 
        empl_full_name, empl_department;

	//TODO: MAKE THIS UNIQUE 
	long empl_ID;
    
	/* Stores the shifts for each employee.
	   Only supports one shift per date  */
    map<string, shift> empl_shifts;
    
public:
    Employee(string empl_full_name, long empl_id, string dept="N/A");
    Employee(string f_name, string l_name, long empl_id, string dept="N/A");
    
    //First Name
	string get_first_name();
	void   set_first_name(string f);

    //Last Name
	string get_last_name();
	void   set_last_name(string l);

	//Full Name
	string get_full_name();
    
    //Department
	string get_department();
	void   set_department(string d);

    //Shifts
    shift get_shift(string d);
    void  set_shift(shift s);
    void  del_shift(string d);

	//Unique Employee ID
	long get_employee_ID() { return empl_ID; };

	//Print Functions
	void print_shifts();
    
    
};

void swap_shift(Employee& A, string A_date, Employee& B, string B_date);

#endif /* defined(__SwapShiftEmployeeClass__Employee__) */







