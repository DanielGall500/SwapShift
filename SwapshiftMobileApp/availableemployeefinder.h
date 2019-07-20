#ifndef AVAILABLEEMPLOYEEFINDER_H
#define AVAILABLEEMPLOYEEFINDER_H

#include <QHash>
#include <QSet>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QQmlEngine>
#include <QDebug>
#include <QObject>
#include <QAbstractListModel>
#include "structs.h"


class AvailableEmployeeFinder : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int shift_indx
               READ shift_indx
               WRITE set_shift_indx
               NOTIFY shift_indx_changed)


    int m_shift_indx;

    QSet<employee> avail_empl;
    QSqlDatabase *db;
    QSqlQuery *query;

    QSet<int> get_all_empl_ID();

    QList<shift> shifts;

public:
    explicit AvailableEmployeeFinder(QSqlDatabase *db, QList<shift> s,  QObject *parent = nullptr);

    QSet<int> get_available_empl_IDs(shift s);

    int shift_indx();

    Q_INVOKABLE void set_shift_indx(const int &indx);
    Q_INVOKABLE QVariant get_available_empl();

signals:
    void shift_indx_changed();



};

#endif // AVAILABLEEMPLOYEEFINDER_H
