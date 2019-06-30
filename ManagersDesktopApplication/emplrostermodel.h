#ifndef EMPLROSTERMODEL_H
#define EMPLROSTERMODEL_H

#include <QAbstractTableModel>
#include <iostream>
#include "EmployeeDatabase/EmployeeDatabase.h"
#include "Structs.h"


class EmplRosterModel : public QAbstractTableModel
{
    Q_OBJECT

    EmployeeDatabase *EMPL_DB;

    map<string, Employee> empl_map;
    map<string, vector<shift>> shift_map;

    roster_info info;

    size_t num_dates, num_empl;

    //Extra header cell for names
    int num_extra_hdrs = 1;
    int hdr_row = 1;


public:
    EmplRosterModel(EmployeeDatabase *empl_db, string title, QObject *parent);
    int rowCount(const QModelIndex &parent = QModelIndex()) const ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    map<string, vector<shift>> parse_roster(string title);
};

#endif // EMPLROSTERMODEL_H
