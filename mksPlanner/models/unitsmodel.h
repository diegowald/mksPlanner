#ifndef UNITSMODEL_H
#define UNITSMODEL_H

#include "models/entitybase.h"
#include "models/modelbase.h"
#include <QMap>


class UnitsModel : public ModelBase
{
    Q_OBJECT
public:
    UnitsModel(QObject *parent = 0);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);

    Qt::ItemFlags flags(const QModelIndex &index) const;

    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex());

protected:
    virtual QString _getSQLRead() const;
    virtual void _loadEntity(QSqlRecord record);
    virtual QList<QSqlQuery*> getQueries(QSqlDatabase &database);
    virtual void markAsSaved();



signals:

public slots:

private:
    QList<int> _entityMapping;
    QMap<int, EntityBasePtr> _entities;
};

typedef QSharedPointer<UnitsModel> UnitsModelPtr;

#endif // UNITSMODEL_H
