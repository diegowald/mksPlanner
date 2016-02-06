#include "rubrosproveedoresmodel.h"
#include "models/rubroroveedor.h"
#include "views/dlgeditrubroproveedor.h"
#include "models/rubro.h"

RubrosProveedoresModel::RubrosProveedoresModel(QObject *parent)
    : ModelBase("tareasProveedores", false, "library", parent)
{
    defineColumnNames();
}

int RubrosProveedoresModel::rowCount(const QModelIndex &/*parent*/) const
{
    return _entityMappingByIdProveedor[_idProveedor].count();
}

void RubrosProveedoresModel::defineColumnNames()
{
    setField(1, "idProveedor");
    setField(2, "idRubro");
    setField(3, "Rubro");
}

/*QVariant RubrosProveedoresModel::headerData(int section, Qt::Orientation orientation, int role) const
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
                return QString("idRubro");
                break;
            }
            case 3:
            {
                return QString("Rubro");
                break;
            }
            default:
                break;
            }
        }
        return section;
    }
    return QAbstractItemModel::headerData(section, orientation, role);
}*/

QVariant RubrosProveedoresModel::modelData(EntityBasePtr entity, int column, int role) const
{
    RubroProveedorPtr rp = qSharedPointerDynamicCast<RubroProveedor>(entity);
    QVariant result;
    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        switch (column)
        {
        case 0:
        {
            result = rp->id();
            break;
        }
        case 1:
        {
            result = rp->idProveedor();
            break;
        }
        case 2:
        {
            result = rp->idRubro();
            break;
        }
        case 3:
        {
            result = rp->idRubro() != -1 ? qSharedPointerDynamicCast<Rubro>(rp->rubro())->name() : "";
            break;
        }
        default:
        {
            result = QVariant();
            break;
        }
        }
    }
    return result;
}

bool RubrosProveedoresModel::modelSetData(EntityBasePtr entity, int column, const QVariant &value, int role)
{
    RubroProveedorPtr rp = qSharedPointerDynamicCast<RubroProveedor>(entity);
    bool result = false;
    if (role == Qt::EditRole)
    {
        switch (column)
        {
        case 1:
        {
            rp->setIdProveedor(value.toInt());
            result = true;
            break;
        }
        case 2:
        {
            rp->setIdRubro(value.toInt());
            result = true;
            break;
        }
        default:
            break;
        }
    }
    return result;
}


QString RubrosProveedoresModel::_getSQLRead() const
{
    return "select * from rubrosProveedores;";
}

int RubrosProveedoresModel::_loadEntity(QSqlRecord record)
{
    int id = record.value(record.indexOf("id")).toInt();
    int idProveedor = record.value("idProveedor").toInt();
    int idRubro = record.value("idRubro").toInt();
    EntityBasePtr entity = RubroProveedorPtr::create(id, idProveedor, idRubro);
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

EntityBasePtr RubrosProveedoresModel::internalCreateEntity(int assignedId)
{
    EntityBasePtr entity = RubroProveedorPtr::create(assignedId);
    qSharedPointerDynamicCast<RubroProveedor>(entity)->setIdProveedor(_idProveedor);
    classifyEntity(entity);
    return entity;
}


void RubrosProveedoresModel::editEntity(int row)
{
    DlgEditRubroProveedor dlg(_idProveedor, this, row);
    dlg.exec();
}

void RubrosProveedoresModel::setIdProveedor(int idProveedor)
{
    _idProveedor = idProveedor;
}

void RubrosProveedoresModel::classifyEntity(EntityBasePtr entity)
{
    RubroProveedorPtr rubroProveedor = qSharedPointerDynamicCast<RubroProveedor>(entity);
    _entityMappingByIdProveedor[rubroProveedor->idProveedor()].append(entity->id());
}

EntityBasePtr RubrosProveedoresModel::getItemByRowid(int row)
{
    int id = _entityMappingByIdProveedor[_idProveedor].at(row);
    return _entities[id];
}

QVariant RubrosProveedoresModel::data(const QModelIndex &index, int role) const
{
    EntityBasePtr entity = _entities[_entityMappingByIdProveedor[_idProveedor].at(index.row())];
    return modelData(entity, index.column(), role);
}

bool RubrosProveedoresModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role == Qt::EditRole)
    {
        EntityBasePtr entity = _entities[_entityMappingByIdProveedor[_idProveedor].at(index.row())];
        modelSetData(entity, index.column(), value, role);
        //entity->setData(index.column(), value, role);
    }
    return true;
}
