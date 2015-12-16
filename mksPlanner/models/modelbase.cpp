#include "modelbase.h"
#include <QDebug>
#include "globalcontainer.h"
#include <QMessageBox>


ModelBase::ModelBase(const QString &counterName, QObject *parent) :
    PersisterBase(),
    QAbstractTableModel(parent)
{
    _counterName = counterName;

}

int ModelBase::rowCount(const QModelIndex &/*parent*/) const
{
    return _entityMapping.count();
}

QVariant ModelBase::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        EntityBasePtr entity = _entities[_entityMapping.at(index.row())];
        return entity->data(index.column(), role);
    }
    else if (role == Qt::EditRole)
    {
        EntityBasePtr entity = _entities[_entityMapping.at(index.row())];
        return entity->data(index.column(), role);
    }
    else
    {
        return QVariant();
    }
}

bool ModelBase::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role == Qt::EditRole)
    {
        EntityBasePtr entity = _entities[_entityMapping.at(index.row())];
        entity->setData(index.column(), value, role);
    }
    return true;
}

Qt::ItemFlags ModelBase::flags(const QModelIndex &index) const
{
    return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
//    return Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}


bool ModelBase::insertRows(int row, int count, const QModelIndex &parent)
{
    //TreeItem *parentItem = getItem(parent);
    bool success;

    beginInsertRows(parent, row, row + count - 1);
    //success = parentItem->insertChildren(position, rows, rootItem->columnCount());
    EntityBasePtr entity = createEntity();
    _entities[entity->id()] = entity;
    _entityMapping.append(entity->id());
    success = true;
    endInsertRows();

    return success;
}


bool ModelBase::removeRow(int row, const QModelIndex &parent)
{
    _entities[_entityMapping.at(row)]->deleteEntity();
    _entityMapping.removeAt(row);
}



QList<QSqlQuery*> ModelBase::getQueries(QSqlDatabase &database)
{
    QList<QSqlQuery*> queries;
    foreach (EntityBasePtr entity, _entities.values())
    {
        QSqlQuery* query = entity->getQuery(database);
        if (query != NULL)
        {
            queries.append(query);
        }
    }
    return queries;
}

void ModelBase::markAsSaved()
{
    foreach (EntityBasePtr entity, _entities.values())
    {
        if (entity->status() == EntityStatus::deleted)
        {
            _entities.remove(entity->id());
        }
        else
        {
            entity->updateStatus(EntityStatus::unchanged);
        }
    }
}

void ModelBase::addEntity(EntityBasePtr entity)
{
    _entities[entity->id()] = entity;
    _entityMapping.append(entity->id());
    int maxId = GlobalContainer::instance().counter(_counterName);
    maxId = (maxId < entity->id()) ? entity->id() : maxId;
    GlobalContainer::instance().setCounter(_counterName, maxId);
}

EntityBasePtr ModelBase::createEntity()
{
    int maxId = GlobalContainer::instance().counter(_counterName);
    if (maxId == -1)
        maxId = 0;
    maxId++;
    EntityBasePtr entity = internalCreateEntity(maxId);
    GlobalContainer::instance().setCounter(_counterName, maxId);
    return entity;
}

void ModelBase::removeEntity(QWidget *parent, int row)
{
    EntityBasePtr entity = getItemByRowid(row);
    if (QMessageBox::question(parent, "Confirmar borrar elemento", "Desea borrar el elemento?", QMessageBox::StandardButton::Yes, QMessageBox::No) == QMessageBox::Yes)
    {
        removeRow(row, QModelIndex());
    }
}

EntityBasePtr ModelBase::getItem(int id)
{
    if (_entities.contains(id))
    {
        return _entities[id];
    }
    else
        return EntityBasePtr();
}

EntityBasePtr ModelBase::getItemByRowid(int row)
{
    qDebug() << row;
    qDebug() << _entityMapping.contains(row);
    qDebug() << _entityMapping[row];
    return getItem(_entityMapping[row]);
}

void ModelBase::setModified()
{
    QModelIndex idx;
    emit dataChanged(idx, idx);
}
