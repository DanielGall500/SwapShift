#include "emplrostermodel.h"

EmplRosterModel::EmplRosterModel(EmployeeDatabase *empl_db, string title,
                                 QObject *parent)
    :QAbstractTableModel(parent), EMPL_DB(empl_db)
{
    info = EMPL_DB->get_roster_info(title);

    num_dates = info.dates.size();
    num_empl  = info.names.size();
}

int EmplRosterModel::rowCount(const QModelIndex & /*parent*/) const
{
    //Rows = Num Employees + Header Row
   return (int)num_empl + hdr_row;
}

int EmplRosterModel::columnCount(const QModelIndex & /*parent*/) const
{
    //Columns = Roster Dates + Any Extra Headers
    return (int)num_dates + num_extra_hdrs;
}

QVariant EmplRosterModel::data(const QModelIndex &index, int role) const
{
    int r = index.row(),
        c = index.column();

    if (role == Qt::DisplayRole)
    {
       return QString("Row%1, Column%2")
                   .arg(index.row() + 1)
                   .arg(index.column() + 1);
    }
    return QVariant();
}

QVariant EmplRosterModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole)
    {
        if(orientation == Qt::Horizontal)
        {
            if (section == 0)
                return QString("Employees");
            else
                return QString::fromStdString(info.dates[section-num_extra_hdrs]);
        }
        else if(orientation == Qt::Vertical)
        {
            return QString::fromStdString(info.names[section-hdr_row]);
        }
    }

    return QVariant();
}
