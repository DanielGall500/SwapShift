//
//  Structs.h
//  SwapShiftEmployeeClass
//
//  Created by Daniel Gallagher on 04/06/2019.
//  Copyright (c) 2019 Developer Co. All rights reserved.
//

#ifndef SwapShiftEmployeeClass_Structs_h
#define SwapShiftEmployeeClass_Structs_h

#include <string>
#include "globals.h"

typedef struct date
{
    int day_of_month, month;

	date() 
	{
		day_of_month = month = 0;
        }

	date(int d, int m) :
		day_of_month(d), month(m)
        {}
    
    //true if x is the same date as y
    bool operator==(const date &x) const
    {
        return ((x.day_of_month == day_of_month) && (x.month == month));
    }
    
    //true if x is earlier in the year than y
    bool operator<(const date &x) const
    {
        if (month < x.month)
        {
            return true;
        }
        else if(month == x.month)
        {
            return (day_of_month < x.day_of_month);
        }
        
        return false;
    }
    
} date;

typedef struct shift
{
	std::string start_time, end_time,
                    roster;

	//TODO: FIX DATES IN ROSTER TO MATCH DATE STRUCT

	//If date can only be string, use str_date
        std::string str_date;
        date shift_date;

        shift() {}

        //If date can be converted to date struct
        shift(date d, std::string start, std::string end, std::string roster) :
            start_time(start), end_time(end), roster(roster), shift_date(d)
        {}

	//If date only exists as string
    shift(std::string d, std::string start, std::string end, std::string roster) :
            start_time(start), end_time(end), roster(roster), str_date(d)
        {}
    
} shift;

typedef struct row_pos
{
    int row, start_pos, end_pos;
    
    //-1 indicates to very end
    row_pos(int r, int s_pos = 0, int e_pos = -1) :
    row(r), start_pos(s_pos), end_pos(e_pos)
    {}
    
    row_pos() {}
} row;

typedef struct col_pos
{
    int col, start_pos, end_pos;
    
    //-1 indicates to very end
    col_pos(int c, int s_pos = 0, int e_pos = -1) :
    col(c), start_pos(s_pos), end_pos(e_pos)
    {}
    
    col_pos() {}
    
} col;

typedef struct roster_info
{
    std::string title;
    vectorStr dates;

    //**UPDATE WHEN ROSTERS CHANGED
    vectorStr names;

    roster_info(std::string t, vectorStr dates, vectorStr names) :
        title(t), dates(dates), names(names)
    {}

    roster_info() {}

    void set_values(std::string t, vectorStr d, vectorStr n)
    {
        title = t;
        dates = d;
        names = n;
    }

} roster_info;

#endif
