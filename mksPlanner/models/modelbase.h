#ifndef MODELBASE_H
#define MODELBASE_H

#include <QObject>
#include "persistance/persister.h"
#include <QAbstractTableModel>
#include <QSharedPointer>
#include "models/entitybase.h"
#include <QMap>
#include <QStyledItemDelegate>

class ModelBase : public QAbstractTableModel, virtual public PersisterBase
{
    Q_OBJECT
public:
    explicit ModelBase(const QString &counterName, bool implementsDelegate, const QString &dbName, QObject *parent = 0);
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    virtual QVariant data(const int id, const int column, int role = Qt::DisplayRole) const;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role);

    Qt::ItemFlags flags(const QModelIndex &index) const;

    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex());
    virtual void editEntity(int row) = 0;

    virtual EntityBasePtr getItem(int id);
    virtual EntityBasePtr getItemByRowid(int row);
    void setModified();

    virtual EntityBasePtr createEntity();
    void removeEntity(QWidget *parent, int row);
    bool removeRow(int row, const QModelIndex &parent);

    virtual QSet<int> ids();
    bool implementsDelegate() const;
    virtual QStyledItemDelegate* delegate();

    virtual int columnIndex(const QString &name) const;

protected:
    virtual QList<QSqlQuery*> getQueries(QSqlDatabase &database);
    virtual void markAsSaved();

    virtual EntityBasePtr internalCreateEntity(int assignedId) = 0;

    void addEntity(EntityBasePtr entity);

    virtual void postProcessData();

    virtual QVariant modelData(EntityBasePtr entity, int column, int role = Qt::DisplayRole) const = 0;
    virtual bool modelSetData(EntityBasePtr entity, int column, const QVariant &value, int role) = 0;
    virtual void defineColumnNames() = 0;
    virtual void setField(int pos, const QString &fieldName);
    QString field(int pos);
signals:

public slots:

protected:
    QList<int> _entityMapping;
    QMap<int, EntityBasePtr> _entities;
    QString _counterName;
    bool _implementsDelegate;
    QMap<int, QString> _fields;
};


#endif // MODELBASE_H
