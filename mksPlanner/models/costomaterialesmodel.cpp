#include "costomaterialesmodel.h"
#include "models/costomaterial.h"
//#include "views/dlgcomponentematerial.h"
//#include <QSet>
//#include "models/material.h"

CostoMaterialesModel::CostoMaterialesModel(QObject *parent) : ModelBase("costoMateriales", parent)
{

}


int CostoMaterialesModel::columnCount(const QModelIndex &parent) const
{
    return 4;
}

/*int CostoMaterialesModel::rowCount(const QModelIndex &/*parent*-/) const
{
    return _entityMappingByIdMaterialPadre[_idMterialPadre].count();
}*/

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
                return QString("idMaterial");
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

/*EntityBasePtr CostoMaterialesModel::getItemByRowid(int row)
{
    int id = _entityMappingByIdMaterialPadre[_idMterialPadre].at(row);
    return _entities[id];
}*/

/*QVariant CostoMaterialesModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        EntityBasePtr entity = _entities[_entityMappingByIdMaterialPadre[_idMterialPadre].at(index.row())];
        return entity->data(index.column(), role);
    }
    else if (role == Qt::EditRole)
    {
        EntityBasePtr entity = _entities[_entityMappingByIdMaterialPadre[_idMterialPadre].at(index.row())];
        return entity->data(index.column(), role);
    }
    else
    {
        return QVariant();
    }
}
*/
/*bool CostoMaterialesModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role == Qt::EditRole)
    {
        EntityBasePtr entity = _entities[_entityMappingByIdMaterialPadre[_idMterialPadre].at(index.row())];
        entity->setData(index.column(), value, role);
    }
    return true;
}
*/
