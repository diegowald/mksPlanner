#include "tareasproveedoresmodel.h"
#include "models/taskproveedor.h"
#include "views/dlgtaskproveedoredit.h"


TareasProveedoresModel::TareasProveedoresModel(QObject *parent) : ModelBase("tareasProveedores", false, parent)
{

}

int TareasProveedoresModel::columnCount(const QModelIndex &parent) const
{
    return 4;
}

int TareasProveedoresModel::rowCount(const QModelIndex &/*parent*/) const
{
    return _entityMappingByIdProveedor[_idProveedor].count();
}

QVariant TareasProveedoresModel::headerData(int section, Qt::Orientation orientation, int role) const
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
                return QString("idProveedor");
                break;
            }
            case 2:
            {
                return QString("idTarea");
                break;
            }
            case 3:
            {
                return QString("Tarea");
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


QString TareasProveedoresModel::_getSQLRead() const
{
    return "select * from tareasProveedores;";
}

int TareasProveedoresModel::_loadEntity(QSqlRecord record)
{
    int id = record.value(record.indexOf("id")).toInt();
    int idProveedor = record.value("idProveedor").toInt();
    int idTask = record.value("idTarea").toInt();
    EntityBasePtr entity = TaskProveedorPtr::create(id, idProveedor, idTask);
    addEntity(entity);
    classifyEntity(entity);
    return id;
}


/*
bool UnitsModel::removeRow(int row, const QModelIndex &parent)
{
    _entities[_entityMapping.at(row)]->deleteEntity();
    _entityMapping.removeAt(row);
}
*/

EntityBasePtr TareasProveedoresModel::internalCreateEntity(int assignedId)
{
    EntityBasePtr entity = TaskProveedorPtr::create(assignedId);
    qSharedPointerDynamicCast<TaskProveedor>(entity)->setIdProveedor(_idProveedor);
    classifyEntity(entity);
    return entity;
}


void TareasProveedoresModel::editEntity(int row)
{
    dlgTaskProveedorEdit dlg(_idProveedor, this, row);
    dlg.exec();
}

void TareasProveedoresModel::setIdProveedor(int idProveedor)
{
    _idProveedor = idProveedor;
}

void TareasProveedoresModel::classifyEntity(EntityBasePtr entity)
{
    TaskProveedorPtr tareaProveedor = qSharedPointerDynamicCast<TaskProveedor>(entity);
    //QMap<int, QMap<int, EntityBasePtr>> _entityMappingByIdMaterialPadre;
    _entityMappingByIdProveedor[tareaProveedor->idProveedor()].append(entity->id());
}

EntityBasePtr TareasProveedoresModel::getItemByRowid(int row)
{
    int id = _entityMappingByIdProveedor[_idProveedor].at(row);
    return _entities[id];
}

QVariant TareasProveedoresModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        EntityBasePtr entity = _entities[_entityMappingByIdProveedor[_idProveedor].at(index.row())];
        return entity->data(index.column(), role);
    }
    else if (role == Qt::EditRole)
    {
        EntityBasePtr entity = _entities[_entityMappingByIdProveedor[_idProveedor].at(index.row())];
        return entity->data(index.column(), role);
    }
    else
    {
        return QVariant();
    }
}

bool TareasProveedoresModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role == Qt::EditRole)
    {
        EntityBasePtr entity = _entities[_entityMappingByIdProveedor[_idProveedor].at(index.row())];
        entity->setData(index.column(), value, role);
    }
    return true;
}
