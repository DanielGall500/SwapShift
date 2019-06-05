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
#include <map>
#include "Structs.h"

using namespace std;

class Employee
{
    
    string empl_first_name;
    
    string empl_last_name;
    
    string empl_department;
    
    map<date, shift> empl_shifts; //only supports one shift per date
    
public:
    Employee(string first_name);
    
    //Set & Get For First Name
    string get_first_name();
    void set_first_name(string f);
    
    //Set & Get For First Name
    string get_last_name();
    void set_last_name(string l);
    
    //Set & Get For Department
    string get_department();
    void set_department(string d);
    
    //Shifts
    shift get_shift(date d);
    void set_shift(shift s);
    
    void del_shift(date d);
    
    
};

void swap_shift(Employee *A, date A_date, Employee *B, date B_date);

#endif /* defined(__SwapShiftEmployeeClass__Employee__) */







