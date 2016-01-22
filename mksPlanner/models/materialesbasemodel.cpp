#include "materialesbasemodel.h"
#include "models/material.h"
#include "views/dlgmaterialeditor.h"

MaterialesBaseModel::MaterialesBaseModel(bool filterByTask, QObject *parent) : ModelBase("materiales", parent)
{
    _filterByTask = filterByTask;
}

int MaterialesBaseModel::columnCount(const QModelIndex &/*parent*/) const
{
    return 7;
}

QVariant MaterialesBaseModel::headerData(int section, Qt::Orientation orientation, int role) const
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
                return QString("Descripción");
                break;
            }
            case 3:
            {
                return QString("Unidad de medida");
                break;
            }
            case 4:
            {
                return QString("Rubro");
                break;
            }
            case 5:
            {
                return QString("Material para usar en planificacion");
                break;
            }
            case 6:
            {
                return QString("Es una tarea");
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


QString MaterialesBaseModel::_getSQLRead() const
{
    return "select * from materiales;";
}

int MaterialesBaseModel::_loadEntity(QSqlRecord record)
{
    int id = record.value(record.indexOf("id")).toInt();
    QString nombre = record.value(record.indexOf("name")).toString();
    QString descripcion = record.value(record.indexOf("description")).toString();
    int idUnit = record.value(record.indexOf("idUnit")).toInt();
    int idRubro = record.value(record.indexOf("idRubro")).toInt();
    bool isUsableMaterial = record.value(record.indexOf("isUsableMaterial")).toBool();
    bool isTask = record.value(record.indexOf("isTask")).toBool();
    bool discard = (_filterByTask + isTask) % 2; // este XOR es true cuando hay que descartar
    if (!discard)
    {
        EntityBasePtr entity = MaterialPtr::create(id, nombre, descripcion, idUnit,idRubro, isUsableMaterial, isTask);
        addEntity(entity);
    }
    return id;
}


/*
bool UnitsModel::removeRow(int row, const QModelIndex &parent)
{
    _entities[_entityMapping.at(row)]->deleteEntity();
    _entityMapping.removeAt(row);
}
*/


void MaterialesBaseModel::editEntity(int row)
{
    dlgMaterialEditor dlg(this, row);
    dlg.exec();
}
