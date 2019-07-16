#ifndef SHIFTREADER_H
#define SHIFTREADER_H

#include <QString>
#include <vector>
#include <QtSql>
#include "structs.h"

using namespace std;

class ShiftReader
{
    QSqlDatabase *db;

public:
    ShiftReader(QSqlDatabase *shifts);

    vector<shift> get_shifts(int employee_ID);


};

#endif // SHIFTREADER_H
