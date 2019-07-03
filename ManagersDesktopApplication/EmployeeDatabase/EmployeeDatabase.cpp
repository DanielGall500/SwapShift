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
                           "VALUES ('%1', '%2', '%3');").arg(f_name).arg(l_name).arg(dept));

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

void EmployeeDatabase::del_employee(string empl_ID)
{
	bool success = false;
	int indx = 0;
    string tmp_ID;

	//Iterate employees in database
	for (Employee &i : empl_db)
	{
        tmp_ID = i.get_unique_ID();

		//Deletion based on ID number
		if (tmp_ID == empl_ID)
		{
			empl_db.erase(empl_db.begin() + indx);
			success = true;
			break;
		}

		indx++;
	}

	if(!success)
		cout << "Employee Not Found" << endl;
	
}

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

Employee EmployeeDatabase::find_employee(int empl_ID)
{
    /* empl_id is unique,
     * thus only one result will be returned */

    QString q = QString("SELECT *"
                        "WHERE empl_ID = %1").arg(empl_ID);

    query->prepare(q);

    if(query->exec())
        qDebug() << "Find Employee Query Executed";
    else
        qDebug() << "Find Employee Query Failed Execution";

    QString f_name = query->value("first_name").toString(),
            l_name = query->value("last_name").toString(),
            dept   = query->value("dept").toString();

    qDebug() << f_name << l_name << dept;

    Employee e(qStr_to_stdStr(f_name),
               qStr_to_stdStr(l_name),
               qStr_to_stdStr(dept));

    return e;
}

QString EmployeeDatabase::query_edit_empl_info(int empl_ID, string col_name, string new_val)
{
    return QString("UPDATE employees"
                   "SET %1 = '%2'"
                   "WHERE empl_ID  = %3").arg(
           QString::fromStdString(col_name)).arg(
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
    string name;
    size_t empl_db_indx;

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

    for (auto &it : empl_shift_map)
    {
        //Name of employee is the map key
        name = it.first;

        //Vector of the shifts as the value
        shifts = it.second;

		//Ensure employee exists in the database
		if (empl_exists(name))
		{
			/* We only have access to the employee's name.
		       Therefore, we have to search using the name
		       instead of ID. */
            empl_db_indx = get_empl_db_indx(name);


			/*Iterate through each shift the employee
              has on this roster. We give each shift to 
              the employee as we iterate through them */
			for (auto& s : shifts)
				empl_db[empl_db_indx].set_shift(s);
        }
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

    *query = QSqlQuery("SELECT *"
                       "FROM employees");

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

bool EmployeeDatabase::empl_exists(string fsize_t_name)
{
    for (Employee& e : get_db_vector())
	{
        if (e.get_full_name() == fsize_t_name)
			return true;
	}

	return false;
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
    size_t indx = 0;

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

bool EmployeeDatabase::has_shift(string name, string date, string roster, shift &return_shift)
{
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





















