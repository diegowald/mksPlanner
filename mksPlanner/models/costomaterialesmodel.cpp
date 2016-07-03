#include "costomaterialesmodel.h"
#include "models/costomaterial.h"
#include "models/costomaterialcompuesto.h"
#include "globalcontainer.h"

//#include "views/dlgcomponentematerial.h"
//#include <QSet>
#include "models/material.h"
#include "models/costomaterialesdelegate.h"
#include <QSet>

CostoMaterialesModel::CostoMaterialesModel(const QDate &fecha, QObject *parent)
    : ModelBase(Tables::CostosUnitarios, "costoMateriales", true, "library", parent)
{
    _crearMaterialCompuesto = false;
    _fecha = fecha;
    defineColumnNames();
    addDependency(static_cast<int>(Tables::MaterialesYTareas));
}


int CostoMaterialesModel::rowCount(const QModelIndex &parent) const
{
    return GlobalContainer::instance().library()->model(Tables::MaterialesYTareas)->rowCount(parent);
    //return _entityMappingByIdMaterialPadre[_idMterialPadre].count();
}

void CostoMaterialesModel::defineColumnNames()
{
    setField(1, "Material",
             [&] (EntityBasePtr, int) -> QVariant
    {
        return QVariant();
    },
    [&] (EntityBasePtr, const QVariant&, int) -> bool
    {
        return false;
    });

    setField(2, "Costo",
             [&] (EntityBasePtr, int) -> QVariant
    {
        return QVariant();
    },
    [&] (EntityBasePtr, const QVariant&, int) -> bool
    {
        return false;
    });

    setField(3, "Precio",
             [&] (EntityBasePtr, int) -> QVariant
    {
        return QVariant();
    },
    [&] (EntityBasePtr, const QVariant&, int) -> bool
    {
        return false;
    });

    setField(4, "Desde",
             [&] (EntityBasePtr, int) -> QVariant
    {
        return QVariant();
    },
    [&] (EntityBasePtr, const QVariant&, int) -> bool
    {
        return false;
    });

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
            result = cm->precio();
            break;
        }
        case 4:
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
    double precio = record.value("precio").toDouble();
    QDate desde = record.value("desde").toDate();
    EntityBasePtr entity = CostoMaterialPtr::create(id, idMaterial, costo, precio, desde);
    addEntity(entity);
    //    _mappingMaterialToCosto[idMaterial] = id;
    _costosPorMaterial.insert(idMaterial, id);
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


void CostoMaterialesModel::editEntity(int)
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
    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        EntityBasePtr entityMaterial = GlobalContainer::instance().library()->model(Tables::MaterialesYTareas)->getItemByRowid(index.row());
        MaterialPtr material = qSharedPointerDynamicCast<Material>(entityMaterial);

        QVariant result = QVariant();
        if (index.column() == 1)
        {
            if (role == Qt::DisplayRole)
            {
                QString r = material->name();
                if (material->isCompuesto())
                {
                    r += " (compuesto)";
                }
                result = r;

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
                            result = cm->precio();
                            break;
                        }
                        case 4:
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
    return QVariant();
}

bool CostoMaterialesModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role == Qt::EditRole)
    {
        EntityBasePtr entity = GlobalContainer::instance().library()->model(Tables::MaterialesYTareas)->getItemByRowid(index.row());
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
        EntityBasePtr entityMaterial = GlobalContainer::instance().library()->model(Tables::MaterialesYTareas)->getItemByRowid(index.row());
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
    _mappingMaterialToCosto.clear();
    QSet<int> idMateriales = GlobalContainer::instance().library()->model(Tables::MaterialesYTareas)->ids();
    foreach (int idMaterial, idMateriales)
    {
        EntityBasePtr entityMaterial = GlobalContainer::instance().library()->model(Tables::MaterialesYTareas)->getItem(idMaterial);
        MaterialPtr material = qSharedPointerDynamicCast<Material>(entityMaterial);

        int idCostoMaterial = buscarIdPorIdMaterial(idMaterial);
        if (idCostoMaterial != -1)
        {
            _mappingMaterialToCosto[idMaterial] = idCostoMaterial;
        }
        else
        {
            //        if (!_mappingMaterialToCosto.contains(entityMaterial->id()))
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


int CostoMaterialesModel::buscarIdPorIdMaterial(int idMaterial)
{
    int id = -1;
    QList<int> costos = _costosPorMaterial.values(idMaterial);

    CostoMaterialPtr costoMastReciente;
    int idConFechaMasReciente = -1;
    foreach (int idCosto, costos)
    {
        CostoMaterialPtr c = cast(getItem(idCosto));
        if (c->desde().toJulianDay() <= _fecha.toJulianDay())
        {
            if (idConFechaMasReciente == -1)
            {
                idConFechaMasReciente = idCosto;
                costoMastReciente = c;
            }
            else
            {
                if (c->desde().toJulianDay() > costoMastReciente->desde().toJulianDay())
                {
                    idConFechaMasReciente = idCosto;
                    costoMastReciente = c;
                }
            }
        }
    }

    id = idConFechaMasReciente;
    return id;
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
            cm->setPrecio(value.toDouble());
            resultado = true;
            break;
        }
        case 4:
        {
            QDate date = value.toDate();
            cm->setDesde(date);
            resultado = true;
            break;
        }
        default:
            break;
        }
    }
    return resultado;
}


CostoMaterialPtr CostoMaterialesModel::cast(EntityBasePtr entity)
{
    return qSharedPointerDynamicCast<CostoMaterial>(entity);
}

void CostoMaterialesModel::setFecha(const QDate &fecha)
{
    _fecha = fecha;
    postProcessData();
}


void CostoMaterialesModel::filtrarPorFecha()
{

}
