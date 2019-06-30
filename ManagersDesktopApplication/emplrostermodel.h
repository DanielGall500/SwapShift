#ifndef EMPLROSTERMODEL_H
#define EMPLROSTERMODEL_H

#include <QAbstractTableModel>
#include <iostream>
#include "EmployeeDatabase/EmployeeDatabase.h"
#include "Structs.h"


class EmplRosterModel : public QAbstractTableModel
{
    Q_OBJECT

    //Pointer to all employees
    EmployeeDatabase *EMPL_DB;

    /* Employee Map:
       Map[Name] = Employee Object */
    map<string, Employee> empl_map;

    /* Shifts Map:
       Map[Name] = Shifts On Roster */
    map<string, vector<shift>> create_shift_map(string title);
    map<string, vector<shift>> shift_map;

    //Roster Information
    roster_info info;


public:
    EmplRosterModel(EmployeeDatabase *empl_db, string title, QObject *parent);
    int rowCount(const QModelIndex &parent = QModelIndex()) const ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

};

#endif // EMPLROSTERMODEL_H
