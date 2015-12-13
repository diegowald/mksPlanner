#include "materialesmodel.h"
#include "models/material.h"
#include "views/dlgmaterialeditor.h"

MaterialesModel::MaterialesModel(QObject *parent) : ModelBase(parent)
{

}

int MaterialesModel::columnCount(const QModelIndex &/*parent*/) const
{
    return 4;
}

QVariant MaterialesModel::headerData(int section, Qt::Orientation orientation, int role) const
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
            default:
                break;
            }
        }
        return section;
    }
    return QAbstractItemModel::headerData(section, orientation, role);
}


QString MaterialesModel::_getSQLRead() const
{
    return "select * from materiales;";
}

void MaterialesModel::_loadEntity(QSqlRecord record)
{
    int id = record.value(record.indexOf("id")).toInt();
    QString nombre = record.value(record.indexOf("name")).toString();
    QString descripcion = record.value(record.indexOf("description")).toString();
    int idUnit = record.value(record.indexOf("idUnit")).toInt();
    EntityBasePtr entity = MaterialPtr::create(id, nombre, descripcion, idUnit);
    addEntity(entity);
}


/*
bool UnitsModel::removeRow(int row, const QModelIndex &parent)
{
    _entities[_entityMapping.at(row)]->deleteEntity();
    _entityMapping.removeAt(row);
}
*/

EntityBasePtr MaterialesModel::internalCreateEntity(int assignedId)
{
    return MaterialPtr::create(assignedId);
}

void MaterialesModel::editEntity(int row)
{
    dlgMaterialEditor dlg(this, row);
    dlg.exec();
}
