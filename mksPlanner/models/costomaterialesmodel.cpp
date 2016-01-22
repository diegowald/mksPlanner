#include "costomaterialesmodel.h"
#include "models/costomaterial.h"
#include "globalcontainer.h"

//#include "views/dlgcomponentematerial.h"
//#include <QSet>
#include "models/material.h"

CostoMaterialesModel::CostoMaterialesModel(QObject *parent) : ModelBase("costoMateriales", parent)
{

}


int CostoMaterialesModel::columnCount(const QModelIndex &parent) const
{
    return 4;
}

int CostoMaterialesModel::rowCount(const QModelIndex &parent) const
{
    return GlobalContainer::instance().materialLibrary()->model(Tables::Materiales)->rowCount(parent);
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


/*
bool UnitsModel::removeRow(int row, const QModelIndex &parent)
{
    _entities[_entityMapping.at(row)]->deleteEntity();
    _entityMapping.removeAt(row);
}
*/

EntityBasePtr CostoMaterialesModel::internalCreateEntity(int assignedId)
{
    EntityBasePtr entity = CostoMaterialPtr::create(assignedId);
    return entity;
}


void CostoMaterialesModel::editEntity(int row)
{/*
    dlgComponenteMaterial dlg(_idMterialPadre, this, row);
    dlg.exec();*/
}

/*void CostoMaterialesModel::setIdMaterialPadre(int idMaterialPadre)
{
    _idMterialPadre = idMaterialPadre;
}*/

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

QVariant CostoMaterialesModel::data(const QModelIndex &index, int role) const
{
    QVariant result = QVariant();
    if (index.column() == 1)
    {
        if (role == Qt::DisplayRole)
        {
            EntityBasePtr entity = GlobalContainer::instance().materialLibrary()->model(Tables::Materiales)->getItemByRowid(index.row());
            MaterialPtr material = qSharedPointerDynamicCast<Material>(entity);
            result = material->name();
        }
    }
    else
    {
        if (_mappingMaterialToCosto.contains(index.row()))
        {
            EntityBasePtr entity = GlobalContainer::instance().materialLibrary()->model(Tables::Materiales)->getItemByRowid(index.row());
            int idCosto = _mappingMaterialToCosto[entity->id()];
            if ((role == Qt::DisplayRole) || (role == Qt::EditRole))
            {
                // ACA HAY UN BUG
                EntityBasePtr entity = _entities[idCosto];
                result = entity->data(index.column(), role);
            }
        }
    }
    return result;
}

bool CostoMaterialesModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role == Qt::EditRole)
    {
        EntityBasePtr entity = GlobalContainer::instance().materialLibrary()->model(Tables::Materiales)->getItemByRowid(index.row());
        int idMaterial = entity->id();
        if (!_mappingMaterialToCosto.contains(index.row()))
        {
            entity = createEntity();
            CostoMaterialPtr cm = qSharedPointerDynamicCast<CostoMaterial>(entity);
            cm->setIdMaterial(idMaterial);
            _mappingMaterialToCosto[idMaterial] = entity->id();
        }
        entity = _entities[_mappingMaterialToCosto[idMaterial]];
        entity->setData(index.column(), value, role);
    }
    return true;
}


Qt::ItemFlags CostoMaterialesModel::flags(const QModelIndex &index) const
{
//    return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
    return Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsEnabled;

}
