//
//  Roster.h
//  SwapShiftEmployeeClass
//
//  Created by Daniel Gallagher on 05/06/2019.
//  Copyright (c) 2019 Developer Co. All rights reserved.
//

#ifndef ROSTER_CLASS_
#define ROSTER_CLASS_

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include "Structs.h"

using namespace std;

class Roster
{
    string file_dir, file_delim;
    
    bool is_header; //column titles e.g Name
    
    unsigned long long file_name_col; //column (starting at 0) which contains the employee names
    
    //Vector filled with entries from csv file
    vector<vector<string>> data_vec;

	//Employee Shift Storage
	map<string, vector<shift>> empl_shifts;
	void read_all_empl_shifts();
    
    //Employee Names
    void read_all_empl_names();
    vector<string> empl_names;

	//Dates of Shifts
	void read_all_shift_dates();
	vector<string> shift_dates;
    
    //Called on creation of class object
    void read_data();
    void parse_data();

	//Creating shift structs from this information
	void parse_shift_times(string shft, string& beg, string& end, string delim="-");

    
public:
    Roster(string f_dir, string delimeter = ", ", int name_col_indx = 0, bool header = false);
    
	//Get Functions
	map<string, vector<shift>> get_empl_shifts() { return empl_shifts; }
	vector<string> get_employee_names() { return empl_names; }
	vector<string> get_shift_dates() { return shift_dates; }
    
    
};

#endif
