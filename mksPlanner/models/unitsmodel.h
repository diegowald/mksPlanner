#ifndef UNITSMODEL_H
#define UNITSMODEL_H

#include <QAbstractTableModel>
#include "models/entitybase.h"
#include <QMap>
#include <persistance/persister.h>


class UnitsModel : public QAbstractTableModel, virtual public PersisterBase
{
    Q_OBJECT
public:
    UnitsModel(const QString &filename, QObject *parent = 0);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);

    Qt::ItemFlags flags(const QModelIndex &index) const;

protected:
    virtual QString _getSQLRead() const;
    virtual void _loadEntity(QSqlRecord record);

signals:

public slots:

private:

    QMap<int, EntityBasePtr> _entities;
};

#endif // UNITSMODEL_H
