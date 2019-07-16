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

#endif // STRUCTS_H]
