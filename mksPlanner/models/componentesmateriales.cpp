#include "componentesmateriales.h"
#include "models/componentematerial.h"
#include "views/dlgcomponentematerial.h"

ComponentesMaterialesModel::ComponentesMaterialesModel(QObject *parent) : ModelBase(parent)
{

}

int ComponentesMaterialesModel::columnCount(const QModelIndex &parent) const
{
    return 4;
}

QVariant ComponentesMaterialesModel::headerData(int section, Qt::Orientation orientation, int role) const
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
                return QString("Cantidad");
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


QString ComponentesMaterialesModel::_getSQLRead() const
{
    return "select * from componentesMateriales;";
}

void ComponentesMaterialesModel::_loadEntity(QSqlRecord record)
{
    int id = record.value(record.indexOf("id")).toInt();
    int idMaterialPadre = record.value("idMaterialPadre").toInt();
    int idMaterial = record.value("idMaterial").toInt();
    double cantidad = record.value("cantidad").toDouble();
    EntityBasePtr entity = ComponenteMaterialPtr::create(id, idMaterialPadre, idMaterial, cantidad);
    addEntity(entity);
}


/*
bool UnitsModel::removeRow(int row, const QModelIndex &parent)
{
    _entities[_entityMapping.at(row)]->deleteEntity();
    _entityMapping.removeAt(row);
}
*/

EntityBasePtr ComponentesMaterialesModel::createEntity()
{
    return ComponenteMaterialPtr::create();
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