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
    date shift_date;
    string start_time, end_time;
    
} shift;


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

void Employee::set_first_name(string f)
{
    empl_first_name = f;
}


//Last Name
string Employee::get_last_name()
{
    return empl_last_name;
}

void Employee::set_last_name(string l)
{
    empl_last_name = l;
}

//Department
string Employee::get_department()
{
    return empl_department;
}

void Employee::set_department(string d)
{
    empl_department = d;
}


//Shifts
void Employee::set_shift(shift s)
{
    empl_shifts[s.shift_date] = s;
}

shift Employee::get_shift(date d)
{
    return empl_shifts[d];
}

void Employee::del_shift(date d)
{
    empl_shifts.erase(d);
}

//Functions
void swap_shift(Employee *A, date A_date, Employee *B, date B_date) //A and Bs original shifts
{
    //Create a temporary variable to hold the shift of emp A
    shift A_temp = A->get_shift(A_date);
    shift B_temp = B->get_shift(B_date);
    
    //Delete shift A and B
    A->del_shift(A_date);
    B->del_shift(B_date);
    
    //Swap the shifts
    A->set_shift(B_temp);
    B->set_shift(A_temp);
    
}

//is_available

int main(int argc, const char * argv[]) {
    
    Employee A("Daniel");
    Employee B("Mark");
    
    date A_date{1,6};
    date B_date{3,6};
    
    shift A_shift{A_date, "18:30", "22:30"};
    shift B_shift{B_date, "14:00", "18:00"};
    
    A.set_shift(A_shift);
    B.set_shift(B_shift);
    
    swap_shift(&A, A_date, &B, B_date);
    
}
















