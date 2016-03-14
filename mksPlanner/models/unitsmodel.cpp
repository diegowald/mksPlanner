#include "unitsmodel.h"

#include "models/unit.h"
#include <QSharedPointer>
#include "views/dlguniteditor.h"
#include <QDebug>

UnitsModel::UnitsModel(QObject *parent) :
    ModelBase(Tables::Unidades, "units", false, "library", parent)
{
    defineColumnNames();
}

void UnitsModel::defineColumnNames()
{
    //setField(1, "Nombre");
    //esto es lo que quiero aramar
    setField(1, "Nombre",
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
    [&] (EntityBasePtr entity, const QVariant& value, int role) -> bool
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
    }
    );
    //setField(2, "Descripción");
    setField(2, "Descripción",
             [&] (EntityBasePtr entity, int role) -> QVariant
    {
        QVariant v;
        switch (role)
        {
        case Qt::DisplayRole:
        case Qt::EditRole:
            v = cast(entity)->description();
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
            cast(entity)->setDescripcion(value.toString());
            return true;
        }
        else
        {
            return false;
        }
    });
}


/*QVariant UnitsModel::modelData(EntityBasePtr entity, int column, int role) const
{
    UnitPtr unit = qSharedPointerDynamicCast<Unit>(entity);
    QVariant result;
    if ((role == Qt::DisplayRole) || (role == Qt::EditRole))
    {
        switch (column)
        {
        case 0:
            result = unit->id();
            break;
        case 1:
            result = unit->name();
            break;
        case 2:
            result = unit->description();
            break;
        default:
            result = QVariant();
            break;
        }
    }
    return result;
}

bool UnitsModel::modelSetData(EntityBasePtr entity, int column, const QVariant &value, int role)
{
    UnitPtr unit = qSharedPointerDynamicCast<Unit>(entity);
    bool result = false;
    switch (column)
    {
    case 0:
        // Se ignora
        result = true;
    case 1:
        unit->setName(value.toString());
        result = true;
        break;
    case 2:
        unit->setDescripcion(value.toString());
        result = true;
        break;
    default:
        result = false;
        break;
    }
    return result;
}*/

QString UnitsModel::_getSQLRead() const
{
    return "select * from units;";
}

int UnitsModel::_loadEntity(QSqlRecord record)
{
    int id = record.value(record.indexOf("id")).toInt();
    QString nombre = record.value(record.indexOf("nombre")).toString();
    QString descripcion = record.value(record.indexOf("descripcion")).toString();
    EntityBasePtr entity = UnitPtr::create(id, nombre, descripcion);
    addEntity(entity);
    return id;
}

EntityBasePtr UnitsModel::internalCreateEntity(int assignedId)
{
    return UnitPtr::create(assignedId);
}


void UnitsModel::editEntity(int row)
{
    dlgUnitEditor dlg(this, row);
    dlg.exec();
}

UnitPtr UnitsModel::cast(EntityBasePtr entity)
{
    return qSharedPointerDynamicCast<Unit>(entity);
}
