#include "EmployeeDatabase.h"
#include "Roster/Roster.h"

EmployeeDatabase::EmployeeDatabase(QSqlDatabase *empl_db, string title) :
    db_title(title), empl_sql_db(empl_db)
{
    this->sql_model = new QSqlQueryModel();
    this->query     = new QSqlQuery(*empl_sql_db);
    
    
    


}

void EmployeeDatabase::refresh_rost_info()
{
    
}

void EmployeeDatabase::add_employee(Employee empl)
{
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
    /* When deleting employee,
     * we need to be sure to delete
     * their shifts also */

    //Handle Employee Table
    query->prepare("DELETE FROM employees "
                   "WHERE empl_id = :ID");

    query->bindValue(":ID", empl_ID);

    if(!query->exec())
        qDebug() << "SQLError: Del Empl 1" << query->lastError();


    //Handle Shifts Table
    query->prepare("DELETE FROM shifts "
                   "WHERE empl_id = :ID");

    query->bindValue(":ID", empl_ID);

    if(!query->exec())
        qDebug() << "SQLError: Del Empl 2" << query->lastError();
	
}

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

QSqlQuery EmployeeDatabase::query_edit_empl_info(int empl_ID, string col_name, string new_val)
{
    QSqlQuery q(*empl_sql_db);

    //STD Str -> QStr
    QString c = QString::fromStdString(col_name);
    QString v = QString::fromStdString(new_val);

    //Cannot bind column name as it will insert quotation marks
    QString str_q = QString("UPDATE employees "
                            "SET %1 = :val "
                            "WHERE empl_id = :empl_id;").arg(c);

    q.prepare(str_q);

    //Bind any values
    q.bindValue(":val", v);
    q.bindValue(":empl_id", empl_ID);

    if(!q.exec())
        qDebug() << "ERROR: "<< q.lastError();

    return q;
}

QSqlQuery EmployeeDatabase::query_get_empl_info(int empl_ID)
{
    QSqlQuery q(*empl_sql_db);

    q.prepare("SELECT * "
              "FROM employees "
              "WHERE empl_id = :empl_id");

    q.bindValue(":empl_id", empl_ID);

    return q;
}

//Edit Employees
void EmployeeDatabase::edit_empl_firstN(int empl_ID, string new_first_name)
{
    QSqlQuery q = query_edit_empl_info(empl_ID, "first_name", new_first_name);

    if(q.exec())
        qDebug() << "Success Edit Empl First Name";
    else
        qDebug() << "Failed Edit Empl First Name";

}

void EmployeeDatabase::edit_empl_lastN(int empl_ID, string new_last_name)
{
    QSqlQuery q = query_edit_empl_info(empl_ID, "last_name", new_last_name);

    if(q.exec())
        qDebug() << "Success Edit Empl Last Name";
    else
        qDebug() << "Failed Edit Empl Last Name";
}

void EmployeeDatabase::edit_empl_dept(int empl_ID, string new_dept)
{
    QSqlQuery q = query_edit_empl_info(empl_ID, "dept", new_dept);

    if(q.exec())
        qDebug() << "Success Edit Empl Dept";
    else
        qDebug() << "Failed Edit Empl Dept";
}

//Get employee info
string EmployeeDatabase::get_empl_firstN(int empl_ID)
{
    QSqlQuery q = query_get_empl_info(empl_ID);

    if(q.exec())
    {
        qDebug() << "Success Get Empl First Name";

        q.first();

        QString fn = q.value("first_name").toString();

        return qStr_to_stdStr(fn);
    }
    else
    {
        qDebug() << "Failed Get Empl First Name"
                 << q.lastError();

        return "ERROR";
    }


}

string EmployeeDatabase::get_empl_lastN(int empl_ID)
{
    QSqlQuery q = query_get_empl_info(empl_ID);

    if(q.exec())
    {
        qDebug() << "Success Get Empl Last Name";

        q.first();

        QString ln = q.value("last_name").toString();

        return qStr_to_stdStr(ln);
    }
    else
    {
        qDebug() << "Failed Get Empl Last Name"
                 << q.lastError();

        return "ERROR";
    }
}

string EmployeeDatabase::get_empl_dept(int empl_ID)
{
    QSqlQuery q = query_get_empl_info(empl_ID);

    if(q.exec())
    {
        qDebug() << "Success Get Empl Dept";

        q.first();

        QString dpt = q.value("dept").toString();

        return qStr_to_stdStr(dpt);
    }
    else
    {
        qDebug() << "Failed Get Empl Department"
                 << q.lastError();

        return "ERROR";
    }
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
    QString fn = QString::fromStdString(f_name),
            ln = QString::fromStdString(l_name);

    query->prepare("SELECT * "
                   "FROM employees "
                   "WHERE first_name = :FN "
                   "AND last_name = :LN ");

    query->bindValue(":FN", fn);
    query->bindValue(":LN", ln);

    if(query->exec())
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





















