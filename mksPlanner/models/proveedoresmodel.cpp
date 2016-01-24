#include "proveedoresmodel.h"

#include <QSharedPointer>
#include "models/proveedor.h"
#include "views/dlgeditproveedor.h"


ProveedoresModel::ProveedoresModel(QObject *parent) : ModelBase("proveedores", false, parent)
{

}

int ProveedoresModel::columnCount(const QModelIndex &/*parent*/) const
{
    return 6;
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
                return QString("Contacto");
                break;
            }
            case 3:
            {
                return QString("eMail");
                break;
            }
            case 4:
            {
                return QString("Telefono");
                break;
            }
            case 5:
            {
                return QString("Dirección");
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

QVariant ProveedoresModel::modelData(EntityBasePtr entity, int column, int role) const
{
    ProveedorPtr prov = qSharedPointerDynamicCast<Proveedor>(entity);
    switch (column)
    {
    case 0:
        return prov->id();
        break;
    case 1:
        return prov->name();
        break;
    case 2:
        return prov->contacto();
        break;
    case 3:
        return prov->email();
        break;
    case 4:
        return prov->telefono();
        break;
    case 5:
        return prov->direccion();
        break;
    default:
        return QVariant();
        break;
    }
}

QString ProveedoresModel::_getSQLRead() const
{
    return "select * from proveedores;";
}

int ProveedoresModel::_loadEntity(QSqlRecord record)
{
    int id = record.value(record.indexOf("id")).toInt();
    QString nombre = record.value(record.indexOf("name")).toString();
    QString contacto = record.value(record.indexOf("contacto")).toString();
    QString email = record.value(record.indexOf("email")).toString();
    QString telefono = record.value(record.indexOf("telefono")).toString();
    QString direccion = record.value(record.indexOf("direccion")).toString();

    EntityBasePtr entity = ProveedorPtr::create(id, nombre, contacto,
                                                email, telefono, direccion);

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
