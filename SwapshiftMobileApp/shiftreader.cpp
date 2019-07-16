#include "shiftreader.h"

ShiftReader::ShiftReader(QSqlDatabase *db) :
    db(db)
{}

QList<shift> ShiftReader::get_shifts(int employee_ID)
{
    QSqlQuery query;

    query.prepare("SELECT * "
                  "FROM shifts "
                  "WHERE empl_id = :ID");

    query.bindValue(":ID", employee_ID);

    if(!query.exec())
    {
        qDebug() << "COULD NOT READ SHIFTS"
                 << query.lastError();

        return QList<shift>();
    }
    else
    {
        QString start_t, end_t, date, rost;
        QList<shift> shifts;

        while(query.next())
        {
            start_t = query.value("start_time").toString();
            end_t   = query.value("end_time").toString();
            date    = query.value("date").toString();
            rost    = query.value("roster").toString();

            shift s(date, start_t, end_t, rost);

            qDebug() << "Reading Shift: "
                     << start_t << end_t
                     << date << rost;

            shifts.push_back(s);
        }

        return shifts;
    }

}
