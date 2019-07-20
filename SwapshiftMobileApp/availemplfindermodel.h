#ifndef AVAILEMPLFINDERMODEL_H
#define AVAILEMPLFINDERMODEL_H

#include <QAbstractListModel>
#include <QDebug>
#include "structs.h"
#include <QList>

class AvailEmplFinderModel : public QAbstractListModel
{
    Q_OBJECT

    QList<employee> avail_empl;

public:
    explicit AvailEmplFinderModel(QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    Q_INVOKABLE void setEmplList(QVector<QVector<QString>> empl);
    
private:
};

#endif // AVAILEMPLFINDERMODEL_H
