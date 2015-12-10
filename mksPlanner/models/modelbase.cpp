#include "modelbase.h"

ModelBase::ModelBase(QObject *parent) :
    PersisterBase(),
    QAbstractTableModel(parent)
{

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

/*
bool UnitsModel::removeRow(int row, const QModelIndex &parent)
{
    _entities[_entityMapping.at(row)]->deleteEntity();
    _entityMapping.removeAt(row);
}
*/


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
}
