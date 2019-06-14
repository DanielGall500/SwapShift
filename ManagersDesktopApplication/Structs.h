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
	std::string start_time, end_time;

	//TODO: FIX DATES IN ROSTER TO MATCH DATE STRUCT

	//If date can only be string, use str_date
	date shift_date;
        std::string str_date;

        shift() {}

	//If date can be converted to date struct
	shift(date d, std::string start, std::string end) :
            start_time(start), end_time(end), shift_date(d)
        {}

	//If date only exists as string
	shift(std::string d, std::string start, std::string end) :
                start_time(start), end_time(end), str_date(d)
        {}
    
} shift;

#endif
