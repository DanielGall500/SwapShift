#include <iostream>
#include <vector>
#include <map>

using namespace std;

typedef struct date
{
    int day_of_month, month;
    
} date;

//true if x is the same date as y
bool operator==(const date x, const date y)
{
    return ((x.day_of_month == y.day_of_month) && (x.month == y.month));
}

//true if x is earlier in the year than y
bool operator<(const date x, const date y)
 {
     if (x.month < y.month)
     {
         return true;
     }
     else if(x.month == y.month)
     {
         return x.day_of_month < y.day_of_month;
     }
     
     return false;
 }

typedef struct shift
{
    string start_time, end_time;
    
} shift;

class Employee
{
    string empl_first_name;
    
    map<date, shift> empl_shifts;
    
public:
    Employee(string first_name);
    
    //Set & Get For First Name
    string get_first_name();
    void set_first_name(string first_name);
    
    //Set & Get For Shifts
    shift get_shift(date x);
    void set_shift(int d, int m, string start_time, string end_time);
    
};

//Constructor
Employee::Employee(string first_name)
{
    empl_first_name = first_name;
}

//First Name
string Employee::get_first_name()
{
    return empl_first_name;
}

void Employee::set_first_name(string first_name)
{
    empl_first_name = first_name;
}

//Shifts
void Employee::set_shift(int d, int m, string start_time, string end_time)
{
    date new_date;
    shift new_shift;
    
    new_date.day_of_month = d;
    new_date.month = m;
    
    new_shift.start_time = start_time;
    new_shift.end_time = end_time;
    
    empl_shifts.insert(pair<date, shift>(new_date, new_shift));
}

shift Employee::get_shift(date x)
{
    return empl_shifts[x];
}


int main(int argc, const char * argv[]) {
    
    Employee x("John");
    
    cout << x.get_first_name() << endl;
    
    x.set_shift(1, 6, "18:30", "22:30");
    
    date d{1,6};
    
    cout << "You start your shift at " << x.get_shift(d).start_time << endl;
    
    
}
