#include "shiftmodel.h"

ShiftModel::ShiftModel(ShiftReader sr, int empl_id, QObject *parent)
    : QAbstractListModel(parent), empl_id(empl_id)
{
    shifts = sr.get_shifts(empl_id);
}

QVariant ShiftModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    // FIXME: Implement me!
}

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

    qDebug() << "DATA";

    if(role == Qt::DisplayRole)
    {
        shift s = shifts.value((int)r);

        QString s_info = s.date + " " +
                         s.start_time + "-" +
                         s.end_time;

        qDebug() << s_info;

        return s_info;
    }
}
