#include "availemplfindermodel.h"

AvailEmplFinderModel::AvailEmplFinderModel(QObject *parent)
    : QAbstractListModel(parent)
{}

QVariant AvailEmplFinderModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    // FIXME: Implement me!
}

int AvailEmplFinderModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return (int)avail_empl.size();
}

QVariant AvailEmplFinderModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    int r = index.row();

    if(role == Qt::DisplayRole)
    {
        employee e = avail_empl.at((int)r);

        QString e_info = e.f_name + " " +
                       e.l_name + ", " + e.dept;

        return e_info;
    }

    return QVariant();
}

void AvailEmplFinderModel::setEmplList(QVector<QVector<QString>> empl)
{
    qDebug() << "New Employee List Set In Model";

    QList<employee> empl_list;

    for(auto &e : empl)
    {
        employee x(e[0],e[1],e[2]);

        empl_list.append(x);
    }

    avail_empl = empl_list;
}
