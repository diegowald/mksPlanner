#include "proveedoresmodel.h"

#include <QSharedPointer>
#include "models/proveedor.h"
#include "views/dlgeditproveedor.h"


ProveedoresModel::ProveedoresModel(QObject *parent) : ModelBase("proveedores", parent)
{

}

int ProveedoresModel::columnCount(const QModelIndex &/*parent*/) const
{
    return 3;
}

QVariant ProveedoresModel::headerData(int section, Qt::Orientation orientation, int role) const
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
                return QString("Telefono");
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


QString ProveedoresModel::_getSQLRead() const
{
    return "select * from proveedores;";
}

int ProveedoresModel::_loadEntity(QSqlRecord record)
{
    int id = record.value(record.indexOf("id")).toInt();
    QString nombre = record.value(record.indexOf("name")).toString();
    QString telefono = record.value(record.indexOf("telefono")).toString();
    EntityBasePtr entity = ProveedorPtr::create(id, nombre, telefono);
    addEntity(entity);
    return id;
}


/*
bool UnitsModel::removeRow(int row, const QModelIndex &parent)
{
    _entities[_entityMapping.at(row)]->deleteEntity();
    _entityMapping.removeAt(row);
}
*/

EntityBasePtr ProveedoresModel::internalCreateEntity(int assignedId)
{
    return ProveedorPtr::create(assignedId);
}


void ProveedoresModel::editEntity(int row)
{
    dlgEditProveedor dlg(this, row);
    dlg.exec();
}
