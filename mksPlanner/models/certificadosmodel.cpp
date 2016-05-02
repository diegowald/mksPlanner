#include "certificadosmodel.h"
#include <QSharedPointer>
//#include "views/dlgEditCertificacion.h"
#include <QSet>
#include "globalcontainer.h"
#include <QDebug>
#include "models/proveedor.h"


CertificadosModel::CertificadosModel(int idProyecto, QObject *parent) :
    ModelBase(Tables::Certificados, "certificados", false, "proyecto", parent)
{
    _idProyecto = idProyecto;
    defineColumnNames();
}

void CertificadosModel::defineColumnNames()
{
    setField(1, "idCertificacion",
             [&] (EntityBasePtr e, int role) -> QVariant
    {
        QVariant v;
        CertificadoPtr c = cast(e);
        switch (role)
        {
        case Qt::DisplayRole:
        case Qt::EditRole:
            v = c->idCertificacion();
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
    setField(4, "Certificado Para Cliente",
             [&] (EntityBasePtr e, int role) -> QVariant
    {
        QVariant v;
        switch (role)
        {
        case Qt::DisplayRole:
            v = cast(e)->isClientCertificate() ? "Si" : "No";
            break;
        case Qt::EditRole:
            v = cast(e)->isClientCertificate();
            break;
        default:
            v = QVariant();
            break;
        }
        return v;
    });

    setField(5, "Nro. Certificado",
             [&] (EntityBasePtr e, int role) -> QVariant
    {
        QVariant v;
        switch (role)
        {
        case Qt::DisplayRole:
        case Qt::EditRole:
            v = cast(e)->nroCertificado();
            break;
        default:
            v = QVariant();
            break;
        }
        return v;
    });

    setField(6, "Status",
             [&] (EntityBasePtr e, int role) -> QVariant
    {
        QVariant v;
        switch (role)
        {
        case Qt::DisplayRole:
        {
            switch (cast(e)->statusCertificado())
            {
            case Certificado::StatusCertificado::Emitido:
                v = "Emitido";
                break;
            case Certificado::StatusCertificado::Abonado:
                v = "Abonado";
                break;
            default:
                v = "";
                break;
            }
        }
            break;
        case Qt::EditRole:
            v = static_cast<int>(cast(e)->statusCertificado());
            break;
        default:
            v = QVariant();
            break;
        }
        return v;
    },
    [&] (EntityBasePtr e, const QVariant &value, int role) -> bool
    {
        if (role == Qt::EditRole)
        {
            cast(e)->setStatusCertificado(static_cast<Certificado::StatusCertificado>(value.toInt()));
            return true;
        }
        return false;
    });

    setField(7, "Fecha Emisión",
             [&] (EntityBasePtr e, int role) -> QVariant
    {
        QVariant v;
        switch (role)
        {
        case Qt::DisplayRole:
        case Qt::EditRole:
            v = cast(e)->fechaEmision();
            break;
        default:
            v = QVariant();
            break;
        }
        return v;
    },
    [&] (EntityBasePtr e, const QVariant &value, int role) -> bool
    {
        if (role == Qt::EditRole)
        {
            cast(e)->setFechaEmision(value.toDate());
            return true;
        }
        return false;
    });

    setField(8, "Desde",
             [&] (EntityBasePtr e, int role) -> QVariant
    {
        QVariant v;
        switch (role)
        {
        case Qt::DisplayRole:
        case Qt::EditRole:
            v = cast(e)->desde();
            break;
        default:
            v = QVariant();
            break;
        }
        return v;
    },
    [&] (EntityBasePtr e, const QVariant &value, int role) -> bool
    {
        if (role == Qt::EditRole)
        {
            cast(e)->setDesde(value.toDate());
            return true;
        }
        return false;
    });

    setField(9, "Hasta",
             [&] (EntityBasePtr e, int role) -> QVariant
    {
        QVariant v;
        switch (role)
        {
        case Qt::DisplayRole:
        case Qt::EditRole:
            v = cast(e)->hasta();
            break;
        default:
            v = QVariant();
            break;
        }
        return v;
    },
    [&] (EntityBasePtr e, const QVariant &value, int role) -> bool
    {
        if (role == Qt::EditRole)
        {
            cast(e)->setHasta(value.toDate());
            return true;
        }
        return false;
    });

}


QString CertificadosModel::_getSQLRead() const
{
    return "select * from certificados;";
}

int CertificadosModel::_loadEntity(QSqlRecord record)
{
    int id = record.value(record.indexOf("id")).toInt();
    int idCertificacion = record.value(record.indexOf("idCertificacion")).toInt();
    int idProveedor = record.value(record.indexOf("idProveedor")).toInt();
    Certificado::StatusCertificado statusCertificado =
            static_cast<Certificado::StatusCertificado>(
                record.value(record.indexOf("statusCertificado")).toInt());
    QDate fechaEmision = record.value(record.indexOf("fechaEmision")).toDate();
    QDate desde = record.value(record.indexOf("desde")).toDate();
    QDate hasta = record.value(record.indexOf("hasta")).toDate();
    QDate fechaPago = record.value(record.indexOf("fechaPago")).toDate();

    EntityBasePtr entity = CertificadoPtr::create(id, idCertificacion, idProveedor,
                                                  statusCertificado,
                                                  fechaEmision, desde, hasta, fechaPago);
    cast(entity)->setIdProyecto(_idProyecto);
    addEntity(entity);
    return id;
}

EntityBasePtr CertificadosModel::internalCreateEntity(int assignedId)
{
    EntityBasePtr entity = CertificadoPtr::create(assignedId);
    cast(entity)->setIdProyecto(_idProyecto);
    return entity;
}


void CertificadosModel::editEntity(int row)
{
    /*    dlgEditCertificacion dlg(this, row);
    dlg.exec();*/
}

CertificadoPtr CertificadosModel::cast(EntityBasePtr entity)
{
    return qSharedPointerDynamicCast<Certificado>(entity);
}

EntityBasePtr CertificadosModel::getItemByCertificacionIdProveedorId(int idCertificacion, int idProveedor)
{
    foreach (int id, ids().values())
    {
        CertificadoPtr c = cast(getItem(id));
        if (c->idCertificacion() == idCertificacion && c->idProveedor() == idProveedor)
        {
            return c;
        }
    }
    return EntityBasePtr();
}
