#include "tareacertificadosmodel.h"
#include <QSharedPointer>
//#include "views/dlgEditCertificacion.h"
#include <QSet>
#include "globalcontainer.h"
#include <QDebug>
#include "models/proveedor.h"
#include "models/executiontask.h"
#include "models/material.h"


TareaCertificadosModel::TareaCertificadosModel(int idProyecto, QObject *parent) :
    ModelBase(Tables::TareaCertificados, "tareaCertificados", false, "proyecto", parent)
{
    _idProyecto = idProyecto;
    defineColumnNames();
}


void TareaCertificadosModel::defineColumnNames()
{
    setField(1, "idCertificacion",
             [&] (EntityBasePtr e, int role) -> QVariant
    {
        QVariant v;
        switch (role)
        {
        case Qt::DisplayRole:
        case Qt::EditRole:
            v = cast(e)->idCertificacion();
            break;
        default:
            v = QVariant();
            break;
        }
        return v;
    },
    [&] (EntityBasePtr e, const QVariant &v, int role) -> bool
    {
        if (role == Qt::EditRole)
        {
            cast(e)->setIdCertificacion(v.toInt());
            return true;
        }
        return false;
    });

    setField(2, "idProveedor",
             [&] (EntityBasePtr e, int role) -> QVariant
    {
        QVariant v;
        switch (role)
        {
        case Qt::DisplayRole:
        case Qt::EditRole:
            v = cast(e)->idProveedor();
            break;
        default:
            v = QVariant();
            break;
        }
        return v;
    });

    setField(3, "Proveedor",
             [&] (EntityBasePtr e, int role) -> QVariant
    {
        QVariant v = QVariant();
        int idProveedor = cast(e)->idProveedor();
        if (idProveedor != -1)
        {
            switch (role)
            {
            case Qt::DisplayRole:
            {
                EntityBasePtr ep = GlobalContainer::instance().library()->model(Tables::Proveedores)->getItem(idProveedor);
                ProveedorPtr p = qSharedPointerDynamicCast<Proveedor>(ep);
                v = p->name();
            }
                break;
            default:
                v = QVariant();
                break;
            }
        }
        return v;
    });
    setField(4, "idTareaEjecucion",
             [&] (EntityBasePtr e, int role) -> QVariant
    {
        QVariant v;
        switch (role)
        {
        case Qt::DisplayRole:
        case Qt::EditRole:
            v = cast(e)->idTareaEjecucion();
            break;
        default:
            v = QVariant();
            break;
        }
        return v;
    });
    setField(5, "Tarea",
             [&] (EntityBasePtr e, int role) -> QVariant
    {
        QVariant v;
        switch (role)
        {
        case Qt::DisplayRole:
        case Qt::EditRole:
        {
            ExecutionTaskPtr ex = qSharedPointerDynamicCast<ExecutionTask>(cast(e)->tareaEjecucion());
            v = ex->name();
            break;
        }
        default:
            v = QVariant();
            break;
        }
        return v;
    });
    setField(6, "Tarea2",
             [&] (EntityBasePtr e, int role) -> QVariant
    {
       QVariant v;
       switch (role)
       {
       case Qt::DisplayRole:
       case Qt::EditRole:
       {
           ExecutionTaskPtr ex = qSharedPointerDynamicCast<ExecutionTask>(cast(e)->tareaEjecucion());
           MaterialPtr m = qSharedPointerDynamicCast<Material>(ex->materialTask());
           v = m->name();
           break;
       }
       default:
           v = QVariant();
           break;
       }
       return v;
    });
    setField(7, "Cantidad",
             [&] (EntityBasePtr e, int role) -> QVariant
    {
        QVariant v;
        switch (role)
        {
        case Qt::DisplayRole:
        case Qt::EditRole:
        {
            ExecutionTaskPtr ex = qSharedPointerDynamicCast<ExecutionTask>(cast(e)->tareaEjecucion());
            v = ex->cantidadToString();
            break;
        }
        default:
            v = QVariant();
            break;
        }
        return v;
    });
    setField(8, "Costo",
             [&] (EntityBasePtr e, int role) -> QVariant
    {
        QVariant v;
        switch (role)
        {
        case Qt::DisplayRole:
        case Qt::EditRole:
        {
            ExecutionTaskPtr ex = qSharedPointerDynamicCast<ExecutionTask>(cast(e)->tareaEjecucion());
            v = ex->costo();
            break;
        }
        default:
            v = QVariant();
            break;
        }
        return v;
    });
    setField(9, "Precio",
             [&] (EntityBasePtr e, int role) -> QVariant
    {
        QVariant v;
        switch (role)
        {
        case Qt::DisplayRole:
        case Qt::EditRole:
        {
            ExecutionTaskPtr ex = qSharedPointerDynamicCast<ExecutionTask>(cast(e)->tareaEjecucion());
            v = ex->precio();
            break;
        }
        default:
            v = QVariant();
            break;
        }
        return v;
    });
}


QString TareaCertificadosModel::_getSQLRead() const
{
    return "select * from tareasCertificados;";
}

int TareaCertificadosModel::_loadEntity(QSqlRecord record)
{
    int id = record.value(record.indexOf("id")).toInt();
    int idCertificacion = record.value(record.indexOf("idCertificacion")).toInt();
    int idProveedor = record.value(record.indexOf("idProveedor")).toInt();
    int idTareaEjecucion = record.value(record.indexOf("idTareaEjecucion")).toInt();

    EntityBasePtr entity = TareaCertificadoPtr::create(id, idCertificacion, idProveedor,
                                                       idTareaEjecucion);
    cast(entity)->setIdProyecto(_idProyecto);
    addEntity(entity);
    return id;
}

EntityBasePtr TareaCertificadosModel::internalCreateEntity(int assignedId)
{
    EntityBasePtr entity = TareaCertificadoPtr::create(assignedId);
    cast(entity)->setIdProyecto(_idProyecto);
    return entity;
}


void TareaCertificadosModel::editEntity(int row)
{
    /*    dlgEditCertificacion dlg(this, row);
    dlg.exec();*/
}

TareaCertificadoPtr TareaCertificadosModel::cast(EntityBasePtr entity)
{
    return qSharedPointerDynamicCast<TareaCertificado>(entity);
}



