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
#include "EmployeeDatabase/EmployeeDatabase.h"
#include "Structs.h"
#include "globals.h"

using namespace std;

class Roster
{
    //Location Of Dates & Names
    col_pos names_loc;
    row_pos dates_loc;

    //Vector filled with entries from csv file
    vectorStr2D roster;
    
    //File Directory, Delimeter & Roster Title
    string file_dir, file_delim, title;
    
    /* This tells us what to ignore on the roster.
       Example: "Hol", "N/A", etc */
    vectorStr non_shifts;
    bool ignore_shift(string shift);

	//Employee Shift Storage & Parsing
	map<string, vector<shift>> empl_shifts;
	void parse_shifts();
    
    //Employee Names & IDs
    vectorStr empl_names;

	//Dates
    vectorStr shift_dates;

	//Creating shift structs from this information
	void parse_shift_times(string shft, string& beg, string& end, string delim="-");
    
    /* Read Row/Column From [Start Position] -> [End Position]
       Start & End Position set to -1 indicates return the whole row/column */
    vectorStr read_roster_row(int row_indx, int start_pos, int end_pos);
    vectorStr read_roster_col(int col_indx, int start_pos, int end_pos);
    string    read_roster_cell(int row_indx,int col_indx);

    
public:
    Roster(string title, vectorStr2D csv_roster, col_pos names, row_pos dates, vectorStr non_shifts);
    
	//Get Functions
	map<string, vector<shift>> get_empl_shifts() { return empl_shifts; }
    vectorStr get_employee_names()               { return empl_names; }
    vectorStr get_shift_dates()                  { return shift_dates; }
    string get_title()                           { return title; }

    //Check Roster Structure & Format
    bool check_formatted_correctly();
    bool check_db_contains_rost_empl(EmployeeDatabase db, string &not_found);

    //Print Func
    void print_summary();
    
    
    
};

#endif
