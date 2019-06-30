#include "emplrostermodel.h"

EmplRosterModel::EmplRosterModel(EmployeeDatabase *empl_db, string title,
                                 QObject *parent)
    :QAbstractTableModel(parent), EMPL_DB(empl_db)
{

    //Get the general roster information
    info = EMPL_DB->get_roster_info(title);

    //Set the number of dates & employees on this roster
    num_dates = info.dates.size();
    num_empl  = info.names.size();

    /*Create employee map
     * Map[Name] = Employee Object */
    empl_map = EMPL_DB->create_empl_map();

    /*Create shift map
     * Map[Name] = Shifts On Roster */
    shift_map = parse_roster(info.title);
}

int EmplRosterModel::rowCount(const QModelIndex & /*parent*/) const
{
    //Rows = Num Employees
   return (int)num_empl;
}

int EmplRosterModel::columnCount(const QModelIndex & /*parent*/) const
{
    //Columns = Roster Dates
    return (int)num_dates;
}

QVariant EmplRosterModel::data(const QModelIndex &index, int role) const
{
    int r = index.row(),
        c = index.column();

    string curr_empl = info.names[r],
           curr_date = info.dates[c];

    //changed func to non-const, is this problem?
    vector<shift> shifts = shift_map.at(curr_empl);

    if (role == Qt::DisplayRole)
    {
        for(shift s : shifts)
        {
            cout << s.str_date << " == " << curr_date << "? " << (s.str_date == curr_date) << endl;
            cout << "----" << endl;

            if(s.str_date == curr_date)
            {
                string shift_str = s.start_time + " - " + s.end_time;
                return QString::fromStdString(shift_str);
            }
        }
    }
    return QString("X");
}

map<string, vector<shift>> EmplRosterModel::parse_roster(string title)
{
    map<string, vector<shift>> rost_map;
    vector<shift> shifts;

    for(string n : info.names)
    {
        //Check if this employee is on the current roster
        map<string, Employee>::iterator it = empl_map.find(n);

        if(it == empl_map.end())
            continue;

        //Create employee
        Employee e = empl_map[n];

        //Add any shifts they have to the roster map
        for(shift s : e.get_all_shifts())
        {
            if(s.roster == title)
            {
                shifts.push_back(s);
            }
        }

        rost_map[n] = shifts;
        shifts.clear();
        shifts.shrink_to_fit();
    }

    return rost_map;
}



QVariant EmplRosterModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole)
    {
        if(orientation == Qt::Horizontal)
        {
            /* --Horizontal Headers--
               Set date as horizontal hdr */

            return QString::fromStdString(info.dates[section]);
        }
        else if(orientation == Qt::Vertical)
        {
            /* --Vertical Headers--
               Set name as vertical hdr */

            return QString::fromStdString(info.names[section]);
        }
    }

    return QVariant();
}
