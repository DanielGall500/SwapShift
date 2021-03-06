//
//  Employee.h
//  SwapShiftEmployeeClass
//
//  Created by Daniel Gallagher on 04/06/2019.
//  Copyright (c) 2019 Developer Co. All rights reserved.
//

#ifndef EMPLOYEE_CLASS
#define EMPLOYEE_CLASS

#include <string>
#include <iostream>
#include <map>
#include <ctime>
#include <cstdlib>
#include <vector>
#include "Structs.h"

using namespace std;

class Employee
{
    
    string empl_first_name, empl_last_name, 
           empl_full_name, empl_department;
    
	/* Stores the shifts for each employee.
	   Only supports one shift per date  */
    map<string, shift> empl_shifts;

    //Generate random ID number
    int empl_unique_ID;
    
public:
    Employee(string f_name, string l_name, string dept="N/A");
    Employee() {}
    
    //First Name
	string get_first_name();
	void   set_first_name(string f);

    //Last Name
	string get_last_name();
	void   set_last_name(string l);

    //Fsize_t Name
    string get_full_name();
    
    //Department
	string get_department();
	void   set_department(string d);

    //Shifts
    vector<shift> get_all_shifts();
    shift get_shift(string d);
    void  set_shift(shift s);
    void  del_shift(string d);

	//Unique Employee ID
    int get_unique_ID();
    void retrieve_unique_ID(int ID); //from SQL database

	//Print Functions
	void print_shifts();
    
    
};

void swap_shift(Employee& A, string A_date, Employee& B, string B_date);

#endif







