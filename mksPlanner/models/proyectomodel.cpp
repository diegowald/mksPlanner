#include "proyectomodel.h"
#include "views/dlgeditproject.h"
#include "models/proyecto.h"


ProyectoModel::ProyectoModel(QObject *parent) : ModelBase("prouecto", false, parent)
{

}

int ProyectoModel::columnCount(const QModelIndex &/*parent*/) const
{
    return 5;
}

QVariant ProyectoModel::headerData(int section, Qt::Orientation orientation, int role) const
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
                return QString("Propietario");
                break;
            }
            case 2:
            {
                return QString("Direccion");
                break;
            }
            case 3:
            {
                return QString("Email");
                break;
            }
            case 4:
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

QVariant ProyectoModel::modelData(EntityBasePtr entity, int column, int role) const
{
    ProyectoPtr p = qSharedPointerDynamicCast<Proyecto>(entity);
    switch (column)
    {
    case 0:
        return p->id();
        break;
    case 1:
    {
        return p->propietario();
        break;
    }
    case 2:
    {
        return p->direccion();
        break;
    }
    case 3:
    {
        return p->email();
        break;
    }
    case 4:
    {
        return p->telefono();
        break;
    }
    default:
        return QVariant();
        break;
    }
}


QString ProyectoModel::_getSQLRead() const
{
    return "select * from proyectos limit 1;";
}

int ProyectoModel::_loadEntity(QSqlRecord record)
{
    int id = record.value(record.indexOf("id")).toInt();
    QString propietario = record.value(record.indexOf("propietario")).toString();
    QString direccion = record.value(record.indexOf("direccion")).toString();
    QString email = record.value(record.indexOf("email")).toString();
    QString telefono = record.value(record.indexOf("telefono")).toString();

    EntityBasePtr entity = ProyectoPtr::create(id, propietario, direccion, email, telefono);
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

EntityBasePtr ProyectoModel::internalCreateEntity(int assignedId)
{
    return ProyectoPtr::create(assignedId);
}


void ProyectoModel::editEntity(int row)
{
    dlgEditProject dlg(this, row);
    dlg.exec();
}
