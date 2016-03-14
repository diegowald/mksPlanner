#include "rubrosmodel.h"
#include "models/rubro.h"
#include <QSharedPointer>
#include "views/dlgeditrubro.h"


RubrosModel::RubrosModel(QObject *parent)
    : ModelBase(Tables::Rubros, "rubros", false, "library", parent)
{
    defineColumnNames();
}


void RubrosModel::defineColumnNames()
{
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
    });

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

    setField(3, "Contiene tareas",
             [&] (EntityBasePtr entity, int role) -> QVariant
    {
        QVariant v;
        switch (role)
        {
        case Qt::DisplayRole:
        case Qt::EditRole:
            v = cast(entity)->isTask();
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
            cast(entity)->setIsTask(value.toBool());
            return true;
        }
        else
        {
            return false;
        }
    });
}

/*QVariant RubrosModel::modelData(EntityBasePtr entity, int column, int role) const
{
    RubroPtr r = qSharedPointerDynamicCast<Rubro>(entity);
    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        switch (column)
        {
        case 0:
            return r->id();
            break;
        case 1:
            return r->name();
            break;
        case 2:
            return r->description();
            break;
        case 3:
            return r->isTask();
            break;
        default:
            return QVariant();
            break;
        }
    }
    return QVariant();
}

bool RubrosModel::modelSetData(EntityBasePtr entity, int column, const QVariant &value, int role)
{
    RubroPtr r = qSharedPointerDynamicCast<Rubro>(entity);
    bool result = false;
    switch (column)
    {
    case 0:
        result = true;
        break;
    case 1:
        r->setName(value.toString());
        result = true;
        break;
    case 2:
        r->setDescripcion(value.toString());
        result = true;
        break;
    case 3:
        r->setIsTask(value.toBool());
        result = true;
        break;
    default:
        break;
    }
    return result;
}*/

QString RubrosModel::_getSQLRead() const
{
    return "select * from rubros;";
}

int RubrosModel::_loadEntity(QSqlRecord record)
{
    int id = record.value(record.indexOf("id")).toInt();
    QString nombre = record.value(record.indexOf("nombre")).toString();
    QString descripcion = record.value(record.indexOf("descripcion")).toString();
    bool isTask = record.value(record.indexOf("isTask")).toBool();
    EntityBasePtr entity = RubroPtr::create(id, nombre, descripcion, isTask);
    addEntity(entity);
    return id;
}


EntityBasePtr RubrosModel::internalCreateEntity(int assignedId)
{
    return RubroPtr::create(assignedId);
}


void RubrosModel::editEntity(int row)
{
    DlgEditRubro dlg(this, row);
    dlg.exec();
}

RubroPtr RubrosModel::cast(EntityBasePtr entity)
{
    return qSharedPointerDynamicCast<Rubro>(entity);
}
