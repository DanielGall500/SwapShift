#include "shiftmodel.h"

ShiftModel::ShiftModel(QList<shift> s, int empl_id, QObject *parent)
    : QAbstractListModel(parent), shifts(s), empl_id(empl_id)
{}

int ShiftModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return (int)shifts.size();

}

QVariant ShiftModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    int r = index.row();

    if(role == Qt::DisplayRole)
    {
        shift s = shifts.value((int)r);

        QString s_info = s.date + " " +
                         s.start_time + "-" +
                         s.end_time;

        return s_info;
    }
}
