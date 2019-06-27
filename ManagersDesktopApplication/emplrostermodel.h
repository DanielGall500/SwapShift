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

    roster_info info;

    ull num_dates, num_empl;

    //Extra header cell for names
    int num_extra_hdrs = 1;
    int hdr_row = 1;

public:
    EmplRosterModel(EmployeeDatabase *empl_db, string title, QObject *parent);
    int rowCount(const QModelIndex &parent = QModelIndex()) const ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
};

#endif // EMPLROSTERMODEL_H
