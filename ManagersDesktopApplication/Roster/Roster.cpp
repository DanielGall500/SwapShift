//
//  Roster.cpp
//  SwapShiftEmployeeClass
//
//  Created by Daniel Gallagher on 05/06/2019.
//  Copyright (c) 2019 Developer Co. All rights reserved.
//

#include "Roster.h"

Roster::Roster(string title, vectorStr2D csv_roster, col_pos names, row_pos dates, vectorStr non_shifts) :
    names_loc(names), dates_loc(dates), roster(csv_roster), title(title), non_shifts(non_shifts)
{
    //-1 => End Of Roster
    if(names_loc.end_pos == -1)
        names_loc.end_pos = (int)roster.size() - 1;
    
    if(dates_loc.end_pos == -1)
        dates_loc.end_pos = (int)roster[0].size() - 1;
    
    /* --Find Names On Roster--
     Names are found on the roster using the names_loc global var, 
     which specifies exactly where the names are located on the roster*/
    
    empl_names = read_roster_col(names_loc.col, names_loc.start_pos, names_loc.end_pos);
    
    /*  --Find Shift Dates On Roster--
     Dates are found using the dates_loc global var,
     specifying where the dates are located on roster*/
    
    shift_dates = read_roster_row(dates_loc.row, dates_loc.start_pos, dates_loc.end_pos);

    parse_shifts();
}

//--SHIFT FUNCTIONS--

void Roster::parse_shifts()
{
    vector<shift> shifts;
    
    /* Each shift is found in a cell that
       corresponds to a date and an employee
       name.
     
       Rows = Names
       Cols = Dates */
    
    int beg_name = names_loc.start_pos,
        end_name = names_loc.end_pos,
        beg_date = dates_loc.start_pos,
        end_date = dates_loc.end_pos;
    
    string name, date, new_shift,
           beg_t, end_t;
    
    for(int n = beg_name; n <= end_name; n++)
    {
        name = read_roster_cell(n, names_loc.col);
        
        for(int d = beg_date; d <= end_date; d++)
        {
            
            date = read_roster_cell(dates_loc.row, d);
            
            new_shift = read_roster_cell(n, d);
            
            /* Some cells will be empty when employees
               do not have a shift that day or will be filled
               with a non-shift such as "Hol", "N/A", etc.*/
            
            if (new_shift.empty() || ignore_shift(new_shift))
                continue;
            
            parse_shift_times(new_shift, beg_t, end_t);
            
            /* --Create Shift--
             ->Date
             ->Beginning Time
             ->End Time
             ->Roster Title (Eg. Week number) */
            
            shift s(date, beg_t, end_t, title);
            
            //Add shift to our shifts vector
            shifts.push_back(s);
            
        }

        //Set name as key, row shifts as value
        empl_shifts[name] = shifts;
        shifts.clear();
    }
}

void Roster::parse_shift_times(string shft, string& beg, string& end, string delim)
{
	size_t pos = shft.find(delim);

	//Start time(everything before the delim)
	beg = shft.substr(0, pos);

	//End time(everything after delim
	end = shft.substr(pos + 1);
}

//--READ ROSTER FUNCTIONS--

vectorStr Roster::read_roster_row(int row_indx, int start_pos, int end_pos)
{
    vectorStr row_cut;
    
    //Cut row from specified start position to specified end position
    row_cut = vectorStr(roster[row_indx].begin() + (start_pos),
                        roster[row_indx].begin() + (end_pos + 1));
    
    return row_cut;
}

vectorStr Roster::read_roster_col(int col_indx, int start_pos, int end_pos)
{
    vectorStr col;
    string entry;
    
    /*Iterate from start position to the end position
      on the column specified*/
    vectorStr2D::iterator row;
    
    for(row = (roster.begin() + (start_pos)); row <= (roster.begin() + (end_pos)); row++)
    {
        //Next entry
        entry = (*row)[col_indx];
        
        //Add to vector
        col.push_back(entry);
    }
    
    return col;
}

string Roster::read_roster_cell(int row_indx, int col_indx)
{
    return roster[row_indx][col_indx];
}

bool Roster::ignore_shift(string shift)
{
    for(string &x : non_shifts)
    {
        if(shift == x)
            return true;
    }
    return false;
}

//TODO: Check Format
bool Roster::check_formatted_correctly()
{
    return true;
}

bool Roster::check_db_contains_rost_empl(EmployeeDatabase db, string &not_found)
{
    vectorStr empl_list = db.get_empl_names();

    cout << "Checking Empl DB" << endl;
    for(string &rost_name : get_employee_names())
    {
        cout << "Checking: " << rost_name << endl;
        if(std::find(empl_list.begin(), empl_list.end(), rost_name) == empl_list.end())
        {
            cout << "FAILED" << endl;
            not_found = rost_name;
            return false;
        }
    }
    return true;
}

//Print Func
void Roster::print_summary()
{
    cout << "--ROSTER SUMMARY--" << endl;
    for(auto &i : empl_shifts)
    {
        cout << "--EMPLOYEE--" << endl;
        cout << "Name: " << i.first << endl;

        for(shift &s : i.second)
        {
            cout << "Shift " << s.str_date
                 << " @" << s.start_time
                 << endl;
        }
        cout << endl;
    }
}













