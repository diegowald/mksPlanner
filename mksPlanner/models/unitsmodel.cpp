#include "unitsmodel.h"

#include "models/unit.h"
#include <QSharedPointer>

UnitsModel::UnitsModel(QObject *parent) :
    ModelBase(parent)
{
    QString m = "m";
    QString d = "metro lineal";
    EntityBasePtr entity = UnitPtr::create(0, m, d);
    _entities[0] = entity;
    _entityMapping.append(0);

    m = "m2";
    d = "metro cuadrado";
    entity = UnitPtr::create(1, m, d);
    _entities[1] = entity;
    _entityMapping.append(1);

    m = "m3";
    d = "metro cubico";
    entity = UnitPtr::create(2, m, d);
    _entities[2] = entity;
    _entityMapping.append(2);

    m = "u.";
    d = "unidad";
    entity = UnitPtr::create(3, m, d);
    _entities[3] = entity;
    _entityMapping.append(3);

    m = "kg";
    d = "kilogramo";
    entity = UnitPtr::create(4, m, d);
    _entities[4] = entity;
    _entityMapping.append(4);

}

int UnitsModel::rowCount(const QModelIndex &/*parent*/) const
{
    return _entityMapping.count();
}

int UnitsModel::columnCount(const QModelIndex &/*parent*/) const
{
    return 2;
}

QVariant UnitsModel::data(const QModelIndex &index, int role) const
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

QVariant UnitsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal)
        {
            switch (section)
            {
            case 0:
            {
                return QString("Nombre");
                break;
            }
            case 1:
            {
                return QString("Descripción");
                break;
            }
            default:
                break;
            }
        }
        return section;
    }
    return QAbstractItemModel::headerData(section, orientation, role);
}

bool UnitsModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role == Qt::EditRole)
    {
        EntityBasePtr entity = _entities[_entityMapping.at(index.row())];
        entity->setData(index.column(), value, role);
    }
    return true;
}

Qt::ItemFlags UnitsModel::flags(const QModelIndex &index) const
{
    return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
//    return Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}


QString UnitsModel::_getSQLRead() const
{
    return "select * from units;";
}

void UnitsModel::_loadEntity(QSqlRecord record)
{
    int id = record.value(record.indexOf("id")).toInt();
    QString nombre = record.value(record.indexOf("nombre")).toString();
    QString descripcion = record.value(record.indexOf("descripcion")).toString();
    EntityBasePtr entity = UnitPtr::create(id, nombre, descripcion);
    _entities[entity->id()] = entity;
    _entityMapping.append(entity->id());
}

bool UnitsModel::insertRows(int row, int count, const QModelIndex &parent)
{
    //TreeItem *parentItem = getItem(parent);
    bool success;

    beginInsertRows(parent, row, row + count - 1);
    //success = parentItem->insertChildren(position, rows, rootItem->columnCount());
    EntityBasePtr entity = UnitPtr::create(-1, "Nueva Unidad", "Nueva Unidad");
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


QList<QSqlQuery*> UnitsModel::getQueries(QSqlDatabase &database)
{
    QList<QSqlQuery*> queries;
    foreach (EntityBasePtr entity, _entities.values())
    {
        UnitPtr unit = qSharedPointerCast<Unit>(entity);
        QSqlQuery* query = unit->getQuery(database);
        if (query != NULL)
        {
            queries.append(query);
        }
    }
    return queries;
}

void UnitsModel::markAsSaved()
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
