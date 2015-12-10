#ifndef MODELBASE_H
#define MODELBASE_H

#include <QObject>
#include "persistance/persister.h"
#include <QAbstractTableModel>
#include <QSharedPointer>
#include "models/entitybase.h"
#include <QMap>

class ModelBase : public QAbstractTableModel, virtual public PersisterBase
{
    Q_OBJECT
public:
    explicit ModelBase(QObject *parent = 0);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);

    Qt::ItemFlags flags(const QModelIndex &index) const;

    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex());
    virtual void editEntity(int row) = 0;

protected:
    virtual QList<QSqlQuery*> getQueries(QSqlDatabase &database);
    virtual void markAsSaved();

    virtual EntityBasePtr createEntity() = 0;

    void addEntity(EntityBasePtr entity);

signals:

public slots:

private:
    QList<int> _entityMapping;
    QMap<int, EntityBasePtr> _entities;
};


#endif // MODELBASE_H