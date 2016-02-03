#include "planningtaskmodel.h"
#include <QSharedPointer>
#include <QDate>
#include "models/planningtask.h"
#include "models/material.h"
#include "models/rubro.h"
#include "models/proveedor.h"
//#include "views/dlgeditproveedor.h"


PlanningTaskModel::PlanningTaskModel(int idProyecto, QObject *parent) : ModelBase("planningtasks", false, "proyectos", parent)
{
    _idProyecto = idProyecto;
    defineColumnNames();
}

int PlanningTaskModel::columnCount(const QModelIndex &/*parent*/) const
{
    return 15;
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
    setField(10, "Fecha Estimada Inicio");
    setField(11, "Fecha Estimada de Finalización");
    setField(12, "Duración");
    setField(13, "Costo");
    setField(14, "Precio");
}

QVariant PlanningTaskModel::headerData(int section, Qt::Orientation orientation, int role) const
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
                return QString("idTareaPadre");
                break;
            }
            case 2:
            {
                return QString("idMaterialTask");
                break;
            }
            case 3:
            {
                return QString("idProveedor");
                break;
            }
            case 4:
            {
                return QString("tareaPadre");
                break;
            }
            case 5:
            {
                return QString("name");
                break;
            }
            case 6:
            {
                return QString("Rubro");
                break;
            }
            case 7:
            {
                return QString ("materialTask");
                break;
            }
            case 8:
            {
                return QString("Proveedor");
                break;
            }
            case 9:
            {
                return QString("Cantidad");
                break;
            }
            case 10:
            {
                return QString("Fecha Estimada Inicio");
                break;
            }
            case 11:
            {
                return QString("Fecha Estimada de Finalización");
                break;
            }
            case 12:
            {
                return QString("Duración");
                break;
            }
            case 13:
            {
                return QString("Costo");
                break;
            }
            case 14:
            {
                return QString("Precio");
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

QVariant PlanningTaskModel::modelData(EntityBasePtr entity, int column, int role) const
{
    PlanningTaskPtr p = qSharedPointerDynamicCast<PlanningTask>(entity);
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
                return r->name();
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
        return QString("Rubro");
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
        return p->fechaEstimadaInicio();
        break;
    }
    case 11:
    {
        return p->fechaEstimadaFin();
        break;
    }
    case 12:
    {
        return p->duracion();
        break;
    }
    case 13:
    {
        return p->costo();
        break;
    }
    case 14:
    {
        return p->precio();
        break;
    }
    default:
        return QVariant();
        break;
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
    {
        QDate date = value.toDate();
        p->setFechaEstimadaInicio(date);
        result = true;
        break;
    }
    case 11:
    {
        QDate date = value.toDate();
        p->setFechaEstimadaFin(date);
        result = true;
        break;
    }
    case 12:
    {
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
    int idMaterialTask = record.value(record.indexOf("idMaterial")).toInt();
    int idProveedor = record.value(record.indexOf("idProveedor")).toInt();
    double cantidad = record.value(record.indexOf("cantidad")).toDouble();
    QDate fechaEstimadaInicio = record.value(record.indexOf("fechaEstimadaInicio")).toDate();
    QDate fechaEstimadaFin = record.value(record.indexOf("fechaEstimadaFin")).toDate();

    EntityBasePtr entity = PlanningTaskPtr::create(id, idTareaPadre,
                                                   name, idMaterialTask, idProveedor,
                                                   cantidad, fechaEstimadaInicio, fechaEstimadaFin);
    qSharedPointerDynamicCast<PlanningTask>(entity)->setIdProyecto(_idProyecto);
    addEntity(entity);
    return id;
}

EntityBasePtr PlanningTaskModel::internalCreateEntity(int assignedId)
{
    return PlanningTaskPtr::create(assignedId);
}


void PlanningTaskModel::editEntity(int row)
{
/*    dlgEditProveedor dlg(this, row);
    dlg.exec();*/
}

EntityBasePtr PlanningTaskModel::createEntity()
{
    EntityBasePtr entity = ModelBase::createEntity();
    qSharedPointerDynamicCast<PlanningTask>(entity)->setIdProyecto(_idProyecto);
    return entity;
}
