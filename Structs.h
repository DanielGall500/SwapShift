//
//  Structs.h
//  SwapShiftEmployeeClass
//
//  Created by Daniel Gallagher on 04/06/2019.
//  Copyright (c) 2019 Developer Co. All rights reserved.
//

#ifndef SwapShiftEmployeeClass_Structs_h
#define SwapShiftEmployeeClass_Structs_h

typedef struct date
{
    int day_of_month, month;

	date() {};

	date(int d, int m) :
		day_of_month(d), month(m)
	{};
    
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
	date shift_date;
	std::string start_time, end_time;

	shift() {};

	shift(date d, std::string start, std::string end) :
		shift_date(d), start_time(start), end_time(end)
	{};
    
} shift;

#endif
