#include "materialesbasemodel.h"
#include "models/material.h"
#include "views/dlgmaterialeditor.h"
#include "models/unit.h"
#include "models/rubro.h"
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
    setField(1, "Rubro",
             [&] (EntityBasePtr entity, int role) -> QVariant
    {
        QVariant v;
        switch (role)
        {
        case Qt::DisplayRole:
        case Qt::EditRole:
            v = cast(entity)->rubro().isNull() ? "" : qSharedPointerDynamicCast<Rubro>(cast(entity)->rubro())->name();
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
            cast(entity)->setRubro(value.toInt());
            return true;
        }
        else
        {
            return false;
        }
    });
    setField(2, "Tarea/Material",
             [&] (EntityBasePtr entity, int role) -> QVariant
    {
        QVariant v;
        switch (role)
        {
        case Qt::DisplayRole:
            if (!cast(entity)->rubro().isNull())
            {
                RubroPtr r = qSharedPointerDynamicCast<Rubro>(cast(entity)->rubro());
                v = (r->isTask()) ? QString("Tarea") : QString("Material");
            }
            else
            {
                v = QVariant();
                break;
        default:
                    v = QVariant();
            }
        }
        return v;
    });

    setField(3, "Nombre",
             [&] (EntityBasePtr entity, int role) -> QVariant
    {
        QVariant v;
        switch (role)
        {
        case Qt::DisplayRole:
        case Qt::EditRole:
            v = cast(entity)->name();
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
            cast(entity)->setName(value.toString());
            return true;
        }
        else
        {
            return false;
        }
    });
    setField(4, "Descripción",
             [&] (EntityBasePtr entity, int role) -> QVariant
    {
        switch (role)
        {
        case Qt::DisplayRole:
        case Qt::EditRole:
            return cast(entity)->description();
            break;
        default:
            return QVariant();
            break;
        }
    },
    [&] (EntityBasePtr entity, const QVariant &value, int role) -> bool
    {
        if (role == Qt::EditRole)
        {
            cast(entity)->setDescription(value.toString());
            return true;
        }
        else
        {
            return false;
        }
    });

    setField(5, "Unidad de medida",
             [&] (EntityBasePtr entity, int role) -> QVariant
    {
        QVariant v;
        switch(role)
        {
        case Qt::DisplayRole:
        case Qt::EditRole:
            if (!cast(entity)->unit().isNull())
            {
                v = qSharedPointerDynamicCast<Unit>(cast(entity)->unit())->name();
            }
            else
            {
                v = QVariant();
            }
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
            cast(entity)->setUnit(value.toInt());
            return true;
        }
        else
        {
            return false;
        }
    });
}

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

MaterialPtr MaterialesBaseModel::cast(EntityBasePtr entity)
{
    return qSharedPointerDynamicCast<Material>(entity);
}
