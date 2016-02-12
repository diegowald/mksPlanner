#include "materialesbasemodel.h"
#include "models/material.h"
#include "views/dlgmaterialeditor.h"
#include "models/unit.h"
#include "models/rubro.h"
#include <QDebug>
#include "globalcontainer.h"

MaterialesBaseModel::MaterialesBaseModel(bool filterByTask, QObject *parent)
    : ModelBase(Tables::Materiales, "materiales", false, "library", parent)
{
    _filterByTask = filterByTask;
    defineColumnNames();
    addDependency(static_cast<int>(Tables::Unidades));
    addDependency(static_cast<int>(Tables::Rubros));
}

void MaterialesBaseModel::defineColumnNames()
{
    setField(1, "Rubro");
    setField(2, "Tarea/Material");
    setField(3, "Nombre");
    setField(4, "Descripción");
    setField(5, "Unidad de medida");
}

/*QVariant MaterialesBaseModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    QVariant result = QVariant();
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal)
        {
            switch (section)
            {
            case 0:
            {
                result = QString("id");
                break;
            }
            case 1:
            {
                result = QString("Rubro");
                break;
            }
            case 2:
            {
                result = QString("Tarea/Material");
                break;
            }
            case 3:
            {
                result = QString("Nombre");
                break;
            }
            case 4:
            {
                result = QString("Descripción");
                break;
            }
            case 5:
            {
                result = QString("Unidad de medida");
                break;
            }
            default:
                break;
            }
        }
        return result;
    }
    return QAbstractItemModel::headerData(section, orientation, role);
}*/

QVariant MaterialesBaseModel::modelData(EntityBasePtr entity, int column, int role) const
{
    MaterialPtr material = qSharedPointerDynamicCast<Material>(entity);
    QVariant result = QVariant();
    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        switch (column)
        {
        case 0:
            result = material->id();
            break;
        case 1:
            if (!material->rubro().isNull())
            {
                result = qSharedPointerDynamicCast<Rubro>(material->rubro())->name();
            }
            break;
        case 2:
            if (!material->rubro().isNull())
            {
                if (qSharedPointerDynamicCast<Rubro>(material->rubro())->isTask())
                {
                    result = QString("Tarea");
                }
                else
                {
                    result = QString("Material");
                }
            }
            break;
        case 3:
            result = material->name();
            break;
        case 4:
            result = material->description();
            break;
        case 5:
            if (!material->unit().isNull())
            {
                result = qSharedPointerDynamicCast<Unit>(material->unit())->name();
            }
            break;
        default:
            break;
        }
    }
    return result;
}

bool MaterialesBaseModel::modelSetData(EntityBasePtr entity, int column, const QVariant &value, int role)
{
    MaterialPtr m = qSharedPointerDynamicCast<Material>(entity);
    bool result = false;
    if (role == Qt::EditRole)
    {
        switch (column)
        {
        case 1:
            m->setRubro(value.toInt());
            result = true;
            break;
        case 3:
            m->setName(value.toString());
            result = true;
            break;
        case 4:
            m->setDescription(value.toString());
            result = true;
            break;
        case 5:
            m->setUnit(value.toInt());
            result = true;
            break;
        default:
            break;
        }
    }
    return result;
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
    bool ok = false;
    int idRubro = record.value(record.indexOf("RubroID")).toInt(&ok);
    EntityBasePtr entity = MaterialPtr::create(id, nombre, descripcion, idUnit, idRubro);
    addEntity(entity);
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
