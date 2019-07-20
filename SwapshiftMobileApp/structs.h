#ifndef STRUCTS_H
#define STRUCTS_H

#include <QString>

typedef struct shift
{
    QString start_time, end_time,
            date, roster;

    shift() {}

    shift(QString d, QString start, QString end, QString roster) :
            start_time(start), end_time(end), date(d), roster(roster)
        {}

} shift;

typedef struct employee
{
    QString f_name, l_name, dept;

    int empl_id;

    employee(QString fn, QString ln, QString dpt, int id) :
        f_name(fn), l_name(ln), dept(dpt), empl_id(id)
    {}

    employee(QString fn, QString ln, QString dpt) :
        f_name(fn), l_name(ln), dept(dpt)
    {}

} employee;

#endif // STRUCTS_H]
