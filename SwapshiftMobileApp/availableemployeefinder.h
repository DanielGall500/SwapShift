#ifndef AVAILABLEEMPLOYEEFINDER_H
#define AVAILABLEEMPLOYEEFINDER_H

#include <QHash>
#include <QSet>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>
#include "structs.h"


class AvailableEmployeeFinder
{

    QSet<employee> avail_empl;
    QSqlDatabase *db;
    QSqlQuery *query;

    QSet<int> get_all_empl_ID();

public:
    AvailableEmployeeFinder(QSqlDatabase *db);

    QSet<int> get_available_empl_IDs(shift s);
    QList<employee> get_available_empl(shift s);



};

#endif // AVAILABLEEMPLOYEEFINDER_H
