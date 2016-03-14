#include "componentesmateriales.h"
#include "models/componentematerial.h"
#include "views/dlgcomponentematerial.h"
#include <QSet>
#include "models/material.h"
#include "models/unit.h"


ComponentesMaterialesModel::ComponentesMaterialesModel(QObject *parent)
    : ModelBase(Tables::ComponentesMateriales, "componentesMateriales", false, "library", parent)
{
    defineColumnNames();
}

int ComponentesMaterialesModel::rowCount(const QModelIndex &) const
{
    return _entityMappingByIdMaterialPadre[_idMterialPadre].count();
}

void ComponentesMaterialesModel::defineColumnNames()
{
    setField(1, "idMaterialPadre",
             [&] (EntityBasePtr entity, int role) -> QVariant
    {
        QVariant v;
        switch (role)
        {
        case Qt::DisplayRole:
        case Qt::EditRole:
            v = cast(entity)->idMaterialPadre();
            break;
        default:
            v = QVariant();
            break;
        }
        return v;
    },
    [&] (EntityBasePtr entity, const QVariant& value, int role) -> bool
    {
        if (role == Qt::EditRole)
        {
            cast(entity)->setIdMaterialPadre(value.toInt());
            return true;
        }
        else
        {
            return false;
        }
    }
    );

    setField(2, "idMaterial",
             [&] (EntityBasePtr entity, int role) -> QVariant
    {
        QVariant v;
        switch (role)
        {
        case Qt::DisplayRole:
        case Qt::EditRole:
            v = cast(entity)->idMaterial();
        break;
        default:
            v = QVariant();
        }
        return v;
    },
    [&] (EntityBasePtr entity, const QVariant &value, int role) -> bool
    {
        if (role == Qt::EditRole)
        {
            cast(entity)->setIdMaterial(value.toInt());
            return true;
        }
        else
        {
            return false;
        }
    });
    setField(3, "Material",
             [&] (EntityBasePtr entity, int role) -> QVariant
    {
        QVariant v;
        switch (role)
        {
        case Qt::DisplayRole:
        case Qt::EditRole:
            v = (cast(entity)->idMaterial() != -1) ?
                        qSharedPointerDynamicCast<Material>(cast(entity)->material())->name() :
                        "";
            break;
        default:
            v = QVariant();
            break;
        }
        return v;
    });
    setField(4, "Cantidad",
             [&] (EntityBasePtr entity, int role) -> QVariant
    {
        QVariant v;
        switch (role)
        {
        case Qt::DisplayRole:
            v = cast(entity)->cantidadToString();
            break;
        case Qt::EditRole:
            v = cast(entity)->cantidad();
            break;
        default:
            v = QVariant();
            break;
        }
        return v;
    },
    [&] (EntityBasePtr entity, const QVariant &value, int role) -> bool
    {
        if (role == Qt::EditRole)
        {
            cast(entity)->setCantidad(value.toDouble());
            return true;
        }
        else
        {
            return false;
        }
    });
}

QVariant ComponentesMaterialesModel::modelData(EntityBasePtr entity, int column, int role) const
{
    ComponenteMaterialPtr comp = qSharedPointerDynamicCast<ComponenteMaterial>(entity);

    QVariant result = QVariant();
    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        switch (column)
        {
        case 0:
        {
            result = comp->id();
            break;
        }
        case 1:
        {
            result = comp->idMaterialPadre();
            break;
        }
        case 2:
        {
            result = comp->idMaterial();
            break;
        }
        case 3:
        {
            result = comp->idMaterial() != -1 ? qSharedPointerDynamicCast<Material>(comp->material())->name() : "";
            break;
        }
        case 4:
        {
            if (role == Qt::DisplayRole)
            {
                result = comp->cantidadToString();
            }
            else
            {
                result = comp->cantidad();
            }
            break;
        }
        case 5:
        {
            if (comp->idMaterial() == -1)
                result = "";
            else
            {
                MaterialPtr mat = qSharedPointerDynamicCast<Material>(comp->material());
                if (mat.isNull())
                    result = "";
                else
                {
                    UnitPtr unit = qSharedPointerDynamicCast<Unit>(mat->unit());
                    result = unit.isNull() ? "" : unit->name();
                }
            }
            break;
        }
        default:
            break;
        }
    }
    return result;
}

bool ComponentesMaterialesModel::modelSetData(EntityBasePtr entity, int column, const QVariant &value, int role)
{
    ComponenteMaterialPtr cm = qSharedPointerDynamicCast<ComponenteMaterial>(entity);
    if (role == Qt::EditRole)
    {
        switch (column)
        {
        case 1:
        {
            cm->setIdMaterialPadre(value.toInt());
            break;
        }
        case 2:
        {
            cm->setIdMaterial(value.toInt());
            break;
        }
        case 4:
        {
            cm->setCantidad(value.toDouble());
            break;
        }
        default:
            break;
        }
        return true;
    }
    return false;
}

QString ComponentesMaterialesModel::_getSQLRead() const
{
    return "select * from componentesMateriales;";
}

int ComponentesMaterialesModel::_loadEntity(QSqlRecord record)
{
    int id = record.value(record.indexOf("id")).toInt();
    int idMaterialPadre = record.value("idMaterialPadre").toInt();
    int idMaterial = record.value("idMaterial").toInt();
    double cantidad = record.value("cantidad").toDouble();
    EntityBasePtr entity = ComponenteMaterialPtr::create(id, idMaterialPadre, idMaterial, cantidad);
    addEntity(entity);
    classifyEntity(entity);
    return id;
}

EntityBasePtr ComponentesMaterialesModel::internalCreateEntity(int assignedId)
{
    EntityBasePtr entity = ComponenteMaterialPtr::create(assignedId);
    qSharedPointerDynamicCast<ComponenteMaterial>(entity)->setIdMaterialPadre(_idMterialPadre);
    classifyEntity(entity);
    return entity;
}


void ComponentesMaterialesModel::editEntity(int row)
{
    dlgComponenteMaterial dlg(_idMterialPadre, this, row);
    dlg.exec();
}

void ComponentesMaterialesModel::setIdMaterialPadre(int idMaterialPadre)
{
    _idMterialPadre = idMaterialPadre;
}

void ComponentesMaterialesModel::classifyEntity(EntityBasePtr entity)
{
    ComponenteMaterialPtr componente = qSharedPointerDynamicCast<ComponenteMaterial>(entity);
    //QMap<int, QMap<int, EntityBasePtr>> _entityMappingByIdMaterialPadre;
    _entityMappingByIdMaterialPadre[componente->idMaterialPadre()].append(entity->id());
}

EntityBasePtr ComponentesMaterialesModel::getItemByRowid(int row)
{
    int id = _entityMappingByIdMaterialPadre[_idMterialPadre].at(row);
    return _entities[id];
}

QVariant ComponentesMaterialesModel::data(const QModelIndex &index, int role) const
{
    EntityBasePtr entity = _entities[_entityMappingByIdMaterialPadre[_idMterialPadre].at(index.row())];
    return modelData(entity, index.column(), role);
}

bool ComponentesMaterialesModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role == Qt::EditRole)
    {
        EntityBasePtr entity = _entities[_entityMappingByIdMaterialPadre[_idMterialPadre].at(index.row())];
        return modelSetData(entity, index.column(), value, role);
        //        entity->setData(index.column(), value, role);
    }
    return true;
}

QSet<int> ComponentesMaterialesModel::compuestosPor(int idMaterial)
{
    QSet<int> result;

    // 1er parte: busco los padres que tienen como componente idMaterial.
    foreach (EntityBasePtr entity, _entities)
    {
        ComponenteMaterialPtr componente = qSharedPointerDynamicCast<ComponenteMaterial>(entity);
        if (componente->idMaterial() == idMaterial)
        {
            result.insert(componente->idMaterialPadre());
        }
    }

    // 2da parte: busco los abuelos
    QSet<int> ids;
    foreach (int idPadre, result)
    {
        ids.unite(compuestosPor(idPadre));
    }

    // 3er parte combino todos los resultados
    result.unite(ids);
    return result;
}

QList<int> ComponentesMaterialesModel::idComponentes(int idMaterialPadre) const
{
    return _entityMappingByIdMaterialPadre[idMaterialPadre];
}

ComponenteMaterialPtr ComponentesMaterialesModel::cast(EntityBasePtr entity)
{
    return qSharedPointerDynamicCast<ComponenteMaterial>(entity);
}
