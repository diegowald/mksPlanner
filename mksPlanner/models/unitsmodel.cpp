#include "unitsmodel.h"

#include "models/unit.h"
#include <QSharedPointer>
#include "views/dlguniteditor.h"

UnitsModel::UnitsModel(QObject *parent) :
    ModelBase("units", parent)
{
}

int UnitsModel::columnCount(const QModelIndex &/*parent*/) const
{
    return 3;
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
                return QString("id");
                break;
            }
            case 1:
            {
                return QString("Nombre");
                break;
            }
            case 2:
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
    addEntity(entity);
}


/*
bool UnitsModel::removeRow(int row, const QModelIndex &parent)
{
    _entities[_entityMapping.at(row)]->deleteEntity();
    _entityMapping.removeAt(row);
}
*/

EntityBasePtr UnitsModel::internalCreateEntity(int assignedId)
{
    return UnitPtr::create(assignedId);
}


void UnitsModel::editEntity(int row)
{
    dlgUnitEditor dlg(this, row);
    dlg.exec();
}
