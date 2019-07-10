#include "EmployeeDatabase.h"
#include "Roster/Roster.h"

EmployeeDatabase::EmployeeDatabase(QSqlDatabase *empl_db, string title) :
    db_title(title), empl_sql_db(empl_db)
{
    this->sql_model = new QSqlQueryModel();
    this->query     = new QSqlQuery(*empl_sql_db);

    vector<Employee> vec = get_db_vector();

}

void EmployeeDatabase::add_employee(Employee empl)
{
    //OLD
	empl_db.push_back(empl);

    //SQL INSERT EMPL
    QString f_name = QString::fromStdString(empl.get_first_name()),
            l_name = QString::fromStdString(empl.get_last_name()),
            dept   = QString::fromStdString(empl.get_department());


    query->prepare(QString("INSERT INTO employees (first_name, last_name, dept) "
                           "VALUES ('%1', '%2', '%3');").arg(f_name, l_name, dept));

    qDebug() << "ADD EMPL" << endl;
    qDebug() << f_name << " " << l_name << " , " << dept;

    if(query->exec())
        qDebug() << "Query Add Empl Successful";
    else
    {
        qDebug() << "Query Add Empl FAILED";
        qDebug() << query->lastError().text();
    }
}

void EmployeeDatabase::del_employee(int empl_ID)
{
    //SQL: Delete from employees
    // AND ALSO shifts database

    //Handle Employee Table
    query->prepare("DELETE FROM employees "
                   "WHERE empl_id = ?");

    query->bindValue("?", empl_ID);

    if(!query->exec())
        qDebug() << "SQLError: Del Empl 1" << query->lastError();


    //Handle Shifts Table
    query->prepare("DELETE FROM shifts "
                   "WHERE empl_id = ?");

    query->bindValue("?", empl_ID);

    if(!query->exec())
        qDebug() << "SQLError: Del Empl 2" << query->lastError();
	
}
/*
//ID safer than name
size_t EmployeeDatabase::get_empl_db_indx(string f_name, string l_name)
{
    size_t indx = 0;

    for (Employee& e : get_db_vector())
    {
        if (f_name == e.get_first_name() &&
            l_name == e.get_last_name())
			break;

		indx++;
	}

	return indx;
}

size_t EmployeeDatabase::get_empl_db_indx(int ID)
{
    size_t indx = 0;

    for (Employee& e : get_db_vector())
    {
        if (ID == e.get_unique_ID())
            break;

        indx++;
    }

    return indx;
}
*/
Employee EmployeeDatabase::find_employee(int empl_ID)
{
    /* empl_id is unique,
     * thus only one result will be returned */

    query->prepare("SELECT * "
                   "FROM employees "
                   "WHERE empl_id = :empl_id");

    query->bindValue(":empl_id", empl_ID);

    if (!query->exec())
    {
        //Error: SQL Cannot Execute Statement
        qDebug() << "Find Employee Query Failed Execution"
                 << query->lastError();

        return Employee();
    }
    else if (query->size() != 1)
    {
        qDebug() << "Invalid Employee ID";
        return Employee();
    }
    else
    {
        query->first();

        QString f_name = query->value("first_name").toString(),
                l_name = query->value("last_name").toString(),
                dept   = query->value("dept").toString();

        qDebug() << f_name << l_name << dept;

        Employee e(qStr_to_stdStr(f_name),
                   qStr_to_stdStr(l_name),
                   qStr_to_stdStr(dept));

        return e;
    }
}

QString EmployeeDatabase::query_edit_empl_info(int empl_ID, string col_name, string new_val)
{
    return QString("UPDATE employees "
                   "SET %1 = '%2' "
                   "WHERE empl_ID  = %3 ").arg(
           QString::fromStdString(col_name),
           QString::fromStdString(new_val)).arg(
                                  empl_ID);
}

QString EmployeeDatabase::query_get_empl_info(int empl_ID, string col_name)
{
    return QString("SELECT %1"
                   "WHERE empl_id = %2").arg(
                QString::fromStdString(col_name)).arg(
                                       empl_ID);
}

//Edit Employees
void EmployeeDatabase::edit_empl_firstN(int empl_ID, string new_first_name)
{
    QString q = query_edit_empl_info(empl_ID, "first_name", new_first_name);

    if(query->exec(q))
        qDebug() << "Success Edit Empl First Name";
    else
        qDebug() << "Failed Edit Empl First Name";

}

void EmployeeDatabase::edit_empl_lastN(int empl_ID, string new_last_name)
{
    QString q = query_edit_empl_info(empl_ID, "last_name", new_last_name);

    if(query->exec(q))
        qDebug() << "Success Edit Empl Last Name";
    else
        qDebug() << "Failed Edit Empl Last Name";
}

void EmployeeDatabase::edit_empl_dept(int empl_ID, string new_dept)
{
    QString q = query_edit_empl_info(empl_ID, "dept", new_dept);

    if(query->exec(q))
        qDebug() << "Success Edit Empl Dept";
    else
        qDebug() << "Failed Edit Empl Dept";
}

//Get employee info
string EmployeeDatabase::get_empl_firstN(int empl_ID)
{
    QString q = query_get_empl_info(empl_ID, "first_name");

    if(query->exec(q))
    {
        qDebug() << "Success Get Empl First Name";
        QString fn = query->value("first_name").toString();

        return qStr_to_stdStr(fn);
    }
    else
        qDebug() << "Failed Get Empl First Name";
        return "Employee Not Found";


}

string EmployeeDatabase::get_empl_lastN(int empl_ID)
{
    QString q = query_get_empl_info(empl_ID, "last_name");

    if(query->exec(q))
    {
        qDebug() << "Success Get Empl Last Name";
        QString ln = query->value("last_name").toString();

        return qStr_to_stdStr(ln);
    }
    else
        qDebug() << "Failed Get Empl last Name";
        return "Employee Not Found";
}

string EmployeeDatabase::get_empl_dept(int empl_ID)
{
    QString q = query_get_empl_info(empl_ID, "dept");

    if(query->exec(q))
    {
        qDebug() << "Success Get Empl Dept";
        QString dpt = query->value("dept").toString();

        return qStr_to_stdStr(dpt);
    }
    else
        qDebug() << "Failed Get Empl Dept";
        return "Employee Not Found";
}

//Roster Functions
void EmployeeDatabase::add_new_roster(Roster& r)
{
    //Declare variables
    map<string, vector<shift>> empl_shift_map = r.get_empl_shifts();
    vector<shift> shifts;

    cout << "Dates: " << r.get_shift_dates().size() << endl;
    cout << "Names: " << r.get_employee_names().size() << endl;

    for(auto s : r.get_employee_names())
    {
        cout << s << endl;
    }

    //Store roster's title, dates and names
    roster_info new_info(r.get_title(),
                         r.get_shift_dates(),
                         r.get_employee_names());

    r_info.push_back(new_info);

    //Placeholder variables
    size_t pos;
    string name, f_name, l_name;

    QString st, et, d, rst;
    int id;

    for (auto &it : empl_shift_map)
    {
        //Name of employee is the map key

        //Employee's Full Name
        name = it.first;

        //Position of space between first and last name
        pos = name.find(' ');

        //Get first and last name
        f_name = name.substr(0, pos);
        l_name = name.substr(pos + 1);

        //Vector of the shifts as the value
        shifts = it.second;

		//Ensure employee exists in the database
        if (empl_exists(f_name, l_name))
		{
            id = get_empl_id(f_name, l_name);

            //insert new shifts for employee
            for(shift s : shifts)
            {
                //Start Time, End Time, Date, Roster
                st   = QString::fromStdString(s.start_time);
                et   = QString::fromStdString(s.end_time);
                d    = QString::fromStdString(s.str_date);
                rst  = QString::fromStdString(s.roster);

                //SQL Query: Insert Shift
                QString q = QString("INSERT INTO shifts (empl_id, start_time, end_time, date, roster) "
                                    "VALUES (%1, '%2', '%3', '%4', '%5')").arg(id).arg(st, et, d, rst);

                //Error if the query cannot execute
                if(!query->exec(q))
                    qDebug() << query->lastError();
            }
        }
        else
            qDebug() << QString("Employee %1 Does Not Exist").arg(QString::fromStdString(name));
    }
}

//Other Functions
void EmployeeDatabase::print_summary()
{
    cout << "--START SUMMARY--"
         << endl << endl;

    for (Employee& e : get_db_vector())
    {
        string name = e.get_full_name();
        vector<shift> shifts = e.get_all_shifts();

        cout << "--EMPLOYEE--" << endl;
        cout << "Name: " << name << endl;

        for(shift &s : shifts)
        {
            cout << "Shift " << s.str_date
                 << " @" << s.start_time
                 << "-" << s.end_time
                 << endl;
        }

        cout << endl << endl;

    }
    cout << "--END SUMMARY--" << endl << endl;
}

vector<Employee> EmployeeDatabase::get_db_vector()
{
    vector<Employee> db_vec;

    query->exec("SELECT * "
                "FROM employees ");

    //Iterate through employees
    while(query->next())
    {
        QString f_name  = query->value("first_name").toString(),
                l_name  = query->value("last_name").toString(),
                dept    = query->value("dept").toString();

        Employee e(qStr_to_stdStr(f_name),
                   qStr_to_stdStr(l_name),
                   qStr_to_stdStr(dept));

        int empl_ID = query->value("empl_ID").toInt();
        e.retrieve_unique_ID(empl_ID);

        db_vec.push_back(e);

    }

    return db_vec;
}

bool EmployeeDatabase::empl_exists(string first_name, string last_name)
{
    //Find an employee with this first & last name
    QString q = QString("SELECT * "
                        "FROM employees "
                        "WHERE first_name = '%1' "
                        "AND   last_name  = '%2' ").arg(
                QString::fromStdString(first_name),
                QString::fromStdString(last_name));

    //Return true if an employee is returned
    if(query->exec(q))
        return (query->size() > 0);
    else
    {
        qDebug() << "Could Not Execute Query: empl_exists";
        return false;
    }
}

vectorStr EmployeeDatabase::get_empl_names()
{
    vectorStr empl_list;

    for(Employee e : get_db_vector())
        empl_list.push_back(e.get_full_name());

    return empl_list;
}

//Get Roster Titles & Dates
vectorStr EmployeeDatabase::get_roster_titles()
{
    vectorStr titles;

    for(roster_info ri : r_info)
        titles.push_back(ri.title);

    return titles;

}

vectorStr2D EmployeeDatabase::get_roster_dates()
{
    vectorStr2D dates;

    for(roster_info ri : r_info)
        dates.push_back(ri.dates);

    return dates;
}

roster_info EmployeeDatabase::get_roster_info(string title)
{
    for(roster_info &r : r_info)
    {
        if(r.title == title)
            return r;
    }

    return roster_info();
}

bool EmployeeDatabase::has_shift(int empl_id, string date, string roster, shift &return_shift)
{
    QString dt  = QString::fromStdString(date),
            rst = QString::fromStdString(roster);

    QString check_shift = QString("SELECT * "
                                  "FROM shifts"
                                  "WHERE empl_id    = %1 "
                                  "AND   date       = '%2' "
                                  "AND   roster     = '%3' ")
                                  .arg(empl_id).arg(dt, rst);


    if(query->exec(check_shift))
    {
        if(query->size() > 0)
        {
            //Get the shift start and end time
            QString strt = query->value("start_time").toString(),
                    end  = query->value("end_time").toString();

            //Set the shift parameter equal to this shift
            return_shift = shift(date, qStr_to_stdStr(strt), qStr_to_stdStr(end), roster);

            return true;
        }
    }
    else
    {
        qDebug() << "Could Not Execute Has Shift Func";
        qDebug() << query->lastError();
    }

    return false;


  /*  //WONT WORK
    int empl_indx = get_empl_db_indx(name, NAME);

    Employee e = get_db_vector()[empl_indx];

    for(shift s : e.get_all_shifts())
    {
        cout << "NEW TEST" << endl;
        if(s.str_date == date && s.roster == roster)
        {
            return_shift = s;
            return true;
        }
    }

    return false;*/
}

map<string, Employee> EmployeeDatabase::create_empl_map()
{
    map<string, Employee> empl_map;

    for(Employee e : get_db_vector())
    {
        empl_map[e.get_full_name()] = e;
    }

    return empl_map;
}

int EmployeeDatabase::get_empl_id(string f_name, string l_name)
{
    QString get_id = QString(
                "SELECT * "
                "FROM employees "
                "WHERE first_name = '%1' "
                "AND last_name = '%2'").arg(
                QString::fromStdString(f_name),
                QString::fromStdString(l_name));

    if(query->exec(get_id))
    {
        query->first();
        return query->value("empl_id").toInt();
    }
    else
    {
        qDebug() << "Employee ID Not Found";
        return -1;
    }


}





















