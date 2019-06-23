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

//MAKE GLOBAL
typedef vector<vector<string>> vectorStr2D;
typedef vector<string> vectorStr;
typedef unsigned long long ull;

class Roster
{
    //Location Of Dates & Names
    row_pos dates_loc;
    col_pos names_loc;
    
    //File Directory, Delimeter & Roster Title
    string file_dir, file_delim, title;
    
    //Vector filled with entries from csv file
    vectorStr2D roster;
    
    /* This tells us what to ignore on the roster.
       Example: "Hol", "N/A", etc */
    vectorStr non_shifts;
    bool ignore_shift(string shift);

	//Employee Shift Storage & Parsing
	map<string, vector<shift>> empl_shifts;
	void parse_shifts();
    
    //Employee Names
    vector<string> empl_names;

	//Dates
	vector<string> shift_dates;

	//Creating shift structs from this information
	void parse_shift_times(string shft, string& beg, string& end, string delim="-");
    
    /* Read Row/Column From [Start Position] -> [End Position]
       Start & End Position set to -1 indicates return the whole row/column */
    vectorStr read_roster_row(int row_indx, int start_pos, int end_pos);
    vectorStr read_roster_col(int col_indx, int start_pos, int end_pos);
    string    read_roster_cell(int row_indx, int col_indx);

    
public:
    Roster(string title, vectorStr2D csv_roster, col_pos names, row_pos dates, vectorStr non_shifts);
    
	//Get Functions
	map<string, vector<shift>> get_empl_shifts() { return empl_shifts; }
	vector<string> get_employee_names() { return empl_names; }
	vector<string> get_shift_dates() { return shift_dates; }
    
    
    
};

#endif
