#include "planningtaskmodel.h"
#include <QSharedPointer>
#include <QDate>
#include "models/planningtask.h"
#include "models/material.h"
#include "models/rubro.h"
#include "models/proveedor.h"
#include "views/dlgeditplanningtask.h"
#include <QDebug>
#include <KDGantt>
#include <models/unit.h>


PlanningTaskModel::PlanningTaskModel(int idProyecto, QObject *parent) : ModelBase("planningtasks", false, "proyectos", parent)
{
    _idProyecto = idProyecto;
    defineColumnNames();
}

void PlanningTaskModel::defineColumnNames()
{
    setField(1, "idTareaPadre");
    setField(2, "idMaterialTask");
    setField(3, "idProveedor");
    setField(4, "tareaPadre");
    setField(5, "name");
    setField(6, "Rubro");
    setField(7, "materialTask");
    setField(8, "Proveedor");
    setField(9, "Cantidad");
    setField(10, "Unidad de medida");
    setField(11, "Fecha Estimada Inicio");
    setField(12, "Fecha Estimada de Finalización");
    setField(13, "Duración");
    setField(14, "Costo");
    setField(15, "Precio");
}

QVariant PlanningTaskModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return ModelBase::headerData(section, orientation, role);
}

QVariant PlanningTaskModel::modelData(EntityBasePtr entity, int column, int role) const
{
    PlanningTaskPtr p = qSharedPointerDynamicCast<PlanningTask>(entity);
    if (role == Qt::DisplayRole)
    {
        switch (column)
        {
        case 0:
        {
            return p->id();
            break;
        }
        case 1:
        {
            return p->idTareaPadre();
            break;
        }
        case 2:
        {
            return p->idMaterialTask();
            break;
        }
        case 3:
        {
            return p->idProveedor();
            break;
        }
        case 4:
        {
            if (p->idTareaPadre() != -1)
            {
                PlanningTaskPtr tp = qSharedPointerDynamicCast<PlanningTask>(p->tareaPadre());
                return tp->name();
            }
            else
            {
                return QVariant();
            }
            break;
        }
        case 5:
        {
            return p->name();
            break;
        }
        case 6:
        {
            if (p->idMaterialTask() != -1)
            {
                MaterialPtr m = qSharedPointerDynamicCast<Material>(p->materialTask());
                if (m->idRubro() != -1)
                {
                    RubroPtr r = qSharedPointerDynamicCast<Rubro>(m->rubro());
                    return r.isNull() ? QVariant() : r->name();
                }
                else
                {
                    return QVariant();
                }
            }
            else
            {
                return QVariant();
            }
            break;
        }
        case 7:
        {
            if (p->idMaterialTask() != -1)
            {
                MaterialPtr m = qSharedPointerDynamicCast<Material>(p->materialTask());
                return m->name();
            }
            else
            {
                return QVariant();
            }
            break;
        }
        case 8:
        {
            if (p->idProveedor() != -1)
            {
                ProveedorPtr prov = qSharedPointerDynamicCast<Proveedor>(p->proveedor());
                return prov->name();
            }
            else
            {
                return QVariant();
            }
            break;
        }
        case 9:
        {
            return p->cantidad();
            break;
        }
        case 10:
        {
            if (p->idMaterialTask() != -1)
            {
                MaterialPtr m = qSharedPointerDynamicCast<Material>(p->materialTask());
                if (m->idUnit() != -1)
                {
                    UnitPtr unit = qSharedPointerDynamicCast<Unit>(m->unit());
                    return unit->name();
                }
                else
                {
                    return QVariant();
                }
            }
            else
            {
                return QVariant();
            }
            break;
        }
        case 11:
        {
            return p->fechaEstimadaInicio();
            break;
        }
        case 12:
        {
            return p->fechaEstimadaFin();
            break;
        }
        case 13:
        {
            return p->duracion();
            break;
        }
        case 14:
        {
            return p->costo();
            break;
        }
        case 15:
        {
            return p->precio();
            break;
        }
        default:
            return QVariant();
            break;
        }
    }
    else if (column == columnCount())
    {
        switch (role)
        {
        case Qt::DisplayRole:
        case Qt::EditRole:
            return p->name();
        case KDGantt::ItemTypeRole:
            return KDGantt::TypeTask;
        case KDGantt::StartTimeRole:
            return p->fechaEstimadaInicio();
        case KDGantt::EndTimeRole:
            return p->fechaEstimadaFin();
        case KDGantt::TaskCompletionRole:
            return QVariant();
            break;
        }
    }
    else
    {
        return QVariant();
    }
}

bool PlanningTaskModel::modelSetData(EntityBasePtr entity, int column, const QVariant &value, int role)
{
    PlanningTaskPtr p = qSharedPointerDynamicCast<PlanningTask>(entity);
    bool result = false;
    switch (column)
    {
    case 0:
        result = true;
        break;
    case 1:
    {
        p->setIdTareaPadre(value.toInt());
        result = true;
        break;
    }
    case 2:
    {
        p->setIdMaterialTask(value.toInt());
        result = true;
        break;
    }
    case 3:
    {
        p->setIdProveedor(value.toInt());
        result = true;
        break;
    }
    case 4:
    {
        break;
    }
    case 5:
    {
        p->setName(value.toString());
        result = true;
        break;
    }
    case 6:
    {
        break;
        break;
    }
    case 7:
    {
        break;
    }
    case 8:
    {
        break;
    }
    case 9:
    {
        p->setCantidad(value.toDouble());
        result = true;
        break;
    }
    case 10:
        break;
    case 11:
    {
        QDateTime date = value.toDateTime();
        p->setFechaEstimadaInicio(date);
        result = true;
        break;
    }
    case 12:
    {
        QDateTime date = value.toDateTime();
        p->setFechaEstimadaFin(date);
        result = true;
        break;
    }
    case 13:
    {
        break;
    }
    case 14:
    {
        break;
    }
    case 15:
    {
        break;
    }
    default:
        break;
    }
    return result;
}

QString PlanningTaskModel::_getSQLRead() const
{
    return "select * from tareasPlanificadas;";
}

int PlanningTaskModel::_loadEntity(QSqlRecord record)
{
    int id = record.value(record.indexOf("id")).toInt();

    int idTareaPadre = record.value(record.indexOf("idTareaPadre")) .toInt();
    QString name = record.value(record.indexOf("name")).toString();
    int idMaterialTask = record.value(record.indexOf("idMaterialTask")).toInt();
    int idProveedor = record.value(record.indexOf("idProveedor")).toInt();
    double cantidad = record.value(record.indexOf("cantidad")).toDouble();
    QDateTime fechaEstimadaInicio = record.value(record.indexOf("fechaEstimadaInicio")).toDateTime();
    QDateTime fechaEstimadaFin = record.value(record.indexOf("fechaEstimadaFin")).toDateTime();

    EntityBasePtr entity = PlanningTaskPtr::create(id, idTareaPadre,
                                                   name, idMaterialTask, idProveedor,
                                                   cantidad, fechaEstimadaInicio, fechaEstimadaFin);
    qSharedPointerDynamicCast<PlanningTask>(entity)->setIdProyecto(_idProyecto);
    addEntity(entity);
    return id;
}

EntityBasePtr PlanningTaskModel::internalCreateEntity(int assignedId)
{
    PlanningTaskPtr p = PlanningTaskPtr::create(assignedId);
    p->setIdProyecto(_idProyecto);
    return p;
}


void PlanningTaskModel::editEntity(int row)
{
    DlgEditPlanningTask dlg(this, row);
    dlg.exec();
}

EntityBasePtr PlanningTaskModel::createEntity()
{
    EntityBasePtr entity = ModelBase::createEntity();
    qSharedPointerDynamicCast<PlanningTask>(entity)->setIdProyecto(_idProyecto);
    return entity;
}

int PlanningTaskModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0; //static_cast<Node*>( idx.internalPointer() )->childCount();
    else
        return ModelBase::rowCount(parent);
}


QList<EntityBasePtr> PlanningTaskModel::tasks() const
{
    return entities();
}
