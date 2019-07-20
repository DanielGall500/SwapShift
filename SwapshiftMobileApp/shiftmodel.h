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
    explicit ShiftModel(QList<shift> s, int empl_id, QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

     int shiftStrRole = Qt::UserRole + 1;

};

#endif // SHIFTMODEL_H
