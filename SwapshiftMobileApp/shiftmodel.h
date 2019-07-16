#ifndef SHIFTMODEL_H
#define SHIFTMODEL_H

#include <QAbstractListModel>
#include "shiftreader.h"

class ShiftModel : public QAbstractListModel
{
    Q_OBJECT

    QList<shift> shifts;

    int empl_id;




public:
    explicit ShiftModel(ShiftReader sr, int empl_id, QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

     int shiftStrRole = Qt::UserRole + 1;

};

#endif // SHIFTMODEL_H
