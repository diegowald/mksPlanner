#include "costomaterialesmodel.h"
#include "models/costomaterial.h"
#include "models/costomaterialcompuesto.h"
#include "globalcontainer.h"

//#include "views/dlgcomponentematerial.h"
//#include <QSet>
#include "models/material.h"
#include "models/costomaterialesdelegate.h"
#include <QSet>

CostoMaterialesModel::CostoMaterialesModel(QObject *parent) : ModelBase("costoMateriales", true, parent)
{
    _crearMaterialCompuesto = false;
}


int CostoMaterialesModel::columnCount(const QModelIndex &/*parent*/) const
{
    return 4;
}

int CostoMaterialesModel::rowCount(const QModelIndex &parent) const
{
    return GlobalContainer::instance().library()->model(Tables::Materiales)->rowCount(parent);
    //return _entityMappingByIdMaterialPadre[_idMterialPadre].count();
}

QVariant CostoMaterialesModel::headerData(int section, Qt::Orientation orientation, int role) const
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
                return QString("Material");
                break;
            }
            case 2:
            {
                return QString("Costo");
                break;
            }
            case 3:
            {
                return QString("Desde");
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

QVariant CostoMaterialesModel::modelData(EntityBasePtr entity, int column, int role) const
{
    CostoMaterialPtr cm = qSharedPointerDynamicCast<CostoMaterial>(entity);
    QVariant result;
    if (role == Qt::DisplayRole)
    {
        switch (column)
        {
        case 0:
        {
            result = cm->id();
            break;
        }
        case 1:
        {
            result = cm->idMaterial();
            break;
        }
        case 2:
        {
            result = cm->costo();
            break;
        }
        case 3:
        {
            result = cm->desde();
            break;
        }
        default:
            break;
        }
    }
    return result;
}

QString CostoMaterialesModel::_getSQLRead() const
{
    return "select * from costosMateriales;";
}

int CostoMaterialesModel::_loadEntity(QSqlRecord record)
{
    int id = record.value(record.indexOf("id")).toInt();
    int idMaterial = record.value("idMaterial").toInt();
    double costo = record.value("costo").toDouble();
    QDate desde = record.value("desde").toDate();
    EntityBasePtr entity = CostoMaterialPtr::create(id, idMaterial, costo, desde);
    addEntity(entity);
    //classifyEntity(entity);
    _mappingMaterialToCosto[idMaterial] = id;
    return id;
}




EntityBasePtr CostoMaterialesModel::internalCreateEntity(int assignedId)
{
    EntityBasePtr entity;
    if (_crearMaterialCompuesto)
    {
        entity = CostoMaterialCompuestoPtr::create(assignedId);
    }
    else
    {
        entity = CostoMaterialPtr::create(assignedId);
    }

    _crearMaterialCompuesto = false;
    return entity;
}


void CostoMaterialesModel::editEntity(int /*row*/)
{
}


EntityBasePtr CostoMaterialesModel::getItemByRowid(int row)
{
    EntityBasePtr entity;
    entity.clear();
    if (_mappingMaterialToCosto.contains(row))
    {
        int idCosto = _mappingMaterialToCosto[row];
        entity = _entities[idCosto];
    }
    return entity;
}

EntityBasePtr CostoMaterialesModel::getItemByIdMaterial(int idMaterial)
{
    EntityBasePtr entity;
    entity.clear();
    if (_mappingMaterialToCosto.contains(idMaterial))
    {
        int idCosto = _mappingMaterialToCosto[idMaterial];
        entity = _entities[idCosto];
    }
    return entity;
}

QVariant CostoMaterialesModel::data(const QModelIndex &index, int role) const
{
    EntityBasePtr entityMaterial = GlobalContainer::instance().library()->model(Tables::Materiales)->getItemByRowid(index.row());
    MaterialPtr material = qSharedPointerDynamicCast<Material>(entityMaterial);

    QVariant result = QVariant();
    if (index.column() == 1)
    {
        if (role == Qt::DisplayRole)
        {
            result = material->name();
        }
    }
    else
    {
        if (_mappingMaterialToCosto.contains(entityMaterial->id()))
        {
            int idCosto = _mappingMaterialToCosto[entityMaterial->id()];
            if ((role == Qt::DisplayRole) || (role == Qt::EditRole))
            {
                EntityBasePtr entity = _entities[idCosto];
                CostoMaterialPtr cm = qSharedPointerDynamicCast<CostoMaterial>(entity);
                if (role == Qt::DisplayRole)
                {
                    switch (index.column())
                    {
                    case 0:
                    {
                        result = cm->id();
                        break;
                    }
                    case 1:
                    {
                        result = cm->idMaterial();
                        break;
                    }
                    case 2:
                    {
                        result = cm->costo();
                        break;
                    }
                    case 3:
                    {
                        result = cm->desde();
                        break;
                    }
                    default:
                        break;
                    }
                }
            }
        }
    }
    return result;
}

bool CostoMaterialesModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role == Qt::EditRole)
    {
        EntityBasePtr entity = GlobalContainer::instance().library()->model(Tables::Materiales)->getItemByRowid(index.row());
        int idMaterial = entity->id();
        if (!_mappingMaterialToCosto.contains(idMaterial))
        {
            entity = createEntity();
            CostoMaterialPtr cm = qSharedPointerDynamicCast<CostoMaterial>(entity);
            cm->setIdMaterial(idMaterial);
            _mappingMaterialToCosto[idMaterial] = entity->id();
        }
        entity = _entities[_mappingMaterialToCosto[idMaterial]];
        modelSetData(entity, index.column(), value, role);
//        entity->setData(index.column(), value, role);
    }
    return true;
}


Qt::ItemFlags CostoMaterialesModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags result = Qt::ItemIsSelectable | Qt::ItemIsEnabled;

    if (index.column() >= 2)
    {
        EntityBasePtr entityMaterial = GlobalContainer::instance().library()->model(Tables::Materiales)->getItemByRowid(index.row());
        MaterialPtr material = qSharedPointerDynamicCast<Material>(entityMaterial);
        if (!material->isCompuesto())
        {
            result = Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsEnabled;
        }
    }
    return result;
}

QStyledItemDelegate *CostoMaterialesModel::delegate()
{
    return new CostoMaterialesDelegate(this);
}

void CostoMaterialesModel::postProcessData()
{
    QSet<int> idMateriales = GlobalContainer::instance().library()->model(Tables::Materiales)->ids();
    foreach (int idMaterial, idMateriales)
    {
        EntityBasePtr entityMaterial = GlobalContainer::instance().library()->model(Tables::Materiales)->getItem(idMaterial);
        MaterialPtr material = qSharedPointerDynamicCast<Material>(entityMaterial);

        if (!_mappingMaterialToCosto.contains(entityMaterial->id()))
        {
            if (material->isCompuesto())
            {
                _crearMaterialCompuesto = true;
                EntityBasePtr entity = createEntity();
                CostoMaterialCompuestoPtr cm = qSharedPointerDynamicCast<CostoMaterialCompuesto>(entity);
                cm->setIdMaterial(idMaterial);
                _mappingMaterialToCosto[idMaterial] = entity->id();
            }
        }
    }
}

bool CostoMaterialesModel::modelSetData(EntityBasePtr entity, int column, const QVariant &value, int role)
{
    CostoMaterialPtr cm = qSharedPointerDynamicCast<CostoMaterial>(entity);
    bool resultado = false;
    if (role == Qt::EditRole)
    {
        switch (column)
        {
        case 1:
        {
            cm->setIdMaterial(value.toInt());
            resultado = true;
            break;
        }
        case 2:
        {
            cm->setCosto(value.toDouble());
            resultado = true;
            break;
        }
        case 3:
        {
            QDate date = value.toDate();
            cm->setDesde(date);
            resultado = true;
            break;
        }
        default:
            break;
        }

        return true;
    }
    return false;
}
