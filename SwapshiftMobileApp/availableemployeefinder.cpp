#include "availableemployeefinder.h"

AvailableEmployeeFinder::AvailableEmployeeFinder(QSqlDatabase *db, QList<shift> s, QObject *parent) :
    QObject(parent), db(db), shifts(s)
{
    this->query = new QSqlQuery(*db);
}

QSet<int> AvailableEmployeeFinder::get_available_empl_IDs(shift s)
{
   /* If employee has any shift with the same date on the same
    * roster, they are defined as not being able to work that day */

    QString date = s.date,
            rost = s.roster;

    QSet<int> avail_empl = get_all_empl_ID();
    QSet<int> unavailable_empl;

    query->prepare("SELECT * "
                "FROM shifts "
                "WHERE date = :D "
                "AND roster = :R ");

    query->bindValue(":D", date);
    query->bindValue(":R", rost);

    if(!query->exec())
    {
        qDebug() << "AVAIL EMPL SQL ERROR" << query->lastError();
        return avail_empl;
    }
    else
    {

        while(query->next())
        {
            int id = query->value("empl_id").toInt();

            unavailable_empl.insert(id);
        }
    }

    //Filter the employees
    avail_empl.subtract(unavailable_empl);

    return avail_empl;
}

QVariant AvailableEmployeeFinder::get_available_empl()
{
    qDebug() << "Finding New Available Employees";

    shift curr_shift = shifts.at(m_shift_indx);

    QSet<int> avail_empl_ids = get_available_empl_IDs(curr_shift);

    QList<employee> avail_empl;
    QVector<QVector<QString>> list;

    query->prepare("SELECT * "
                   "FROM employees ");

    if(!query->exec())
        qDebug() << "AVAIL EMPL ERR" << query->lastError();
    else
    {

        while(query->next())
        {
            int id = query->value("empl_id").toInt();

            if(avail_empl_ids.contains(id))
            {
                QString f_name = query->value("first_name").toString(),
                        l_name = query->value("last_name").toString(),
                        dept   = query->value("dept").toString();

                list.append({f_name, l_name, dept});

                employee e(f_name, l_name, dept, id);

                avail_empl.push_back(e);
            }
        }
    }

    //Convert to QML format
    QVariant output = QVariant::fromValue(list);

    return output;
}

QSet<int> AvailableEmployeeFinder::get_all_empl_ID()
{

    query->prepare("SELECT * "
                   "FROM employees ");

    QSet<int> empl;


    if(!query->exec())
        qDebug() << "ALL AVAIL EMPL SQL ERR" << query->lastError();
    else
    {
        while(query->next())
        {
            int id = query->value("empl_id").toInt();

            empl.insert(id);
        }
    }

    return empl;
}

void AvailableEmployeeFinder::set_shift_indx(const int &indx)
{
    qDebug() << "SHIFT INDX CHANGED" << indx;

    if(indx == m_shift_indx)
        return;

    m_shift_indx = indx;

    emit shift_indx_changed();
}

int AvailableEmployeeFinder::shift_indx()
{
    return m_shift_indx;
}























