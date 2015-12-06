#include "unitsmodel.h"

#include "models/unit.h"
#include <QSharedPointer>

UnitsModel::UnitsModel(const QString &filename, QObject *parent) :
    QAbstractTableModel(parent), PersisterBase(filename, parent)
{
    QString m = "m";
    QString d = "metro lineal";
    EntityBasePtr entity = UnitPtr::create(0, m, d);
    _entities[0] = entity;

    m = "m2";
    d = "metro cuadrado";
    entity = UnitPtr::create(1, m, d);
    _entities[1] = entity;

    m = "m3";
    d = "metro cubico";
    entity = UnitPtr::create(2, m, d);
    _entities[2] = entity;

    m = "u.";
    d = "unidad";
    entity = UnitPtr::create(3, m, d);
    _entities[3] = entity;

    m = "kg";
    d = "kilogramo";
    entity = UnitPtr::create(4, m, d);
    _entities[4] = entity;

}

int UnitsModel::rowCount(const QModelIndex &/*parent*/) const
{
    return _entities.count();
}

int UnitsModel::columnCount(const QModelIndex &/*parent*/) const
{
    return 2;
}

QVariant UnitsModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        EntityBasePtr entity = _entities[index.row()];
        return entity->data(index.column(), role);
    }
    else if (role == Qt::EditRole)
    {
        EntityBasePtr entity = _entities[index.row()];
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
        EntityBasePtr entity = _entities[index.row()];
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
}
