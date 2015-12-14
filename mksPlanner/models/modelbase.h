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
    explicit ModelBase(const QString &counterName, QObject *parent = 0);
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role);

    Qt::ItemFlags flags(const QModelIndex &index) const;

    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex());
    virtual void editEntity(int row) = 0;

    virtual EntityBasePtr getItem(int id);
    virtual EntityBasePtr getItemByRowid(int row);
    void setModified();

    EntityBasePtr createEntity();
protected:
    virtual QList<QSqlQuery*> getQueries(QSqlDatabase &database);
    virtual void markAsSaved();

    virtual EntityBasePtr internalCreateEntity(int assignedId) = 0;

    void addEntity(EntityBasePtr entity);

signals:

public slots:

protected:
    QList<int> _entityMapping;
    QMap<int, EntityBasePtr> _entities;
    QString _counterName;

};


#endif // MODELBASE_H
