#include "certificacionesmodel.h"
#include <QSharedPointer>
#include "views/dlgEditCertificacion.h"
#include <QSet>

#include <QDebug>

CertificacionesModel::CertificacionesModel(int idProyecto, QObject *parent) :
    ModelBase(Tables::Certificaciones, "certificaciones", false, "proyecto", parent)
{
    _idProyecto = idProyecto;
    defineColumnNames();
}

void CertificacionesModel::defineColumnNames()
{
    setField(1, "Fecha",
             [&] (EntityBasePtr entity, int role) -> QVariant
    {
        QVariant v;
        switch (role)
        {
        case Qt::DisplayRole:
        case Qt::EditRole:
            v = cast(entity)->fechaCertificacion();
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
            cast(entity)->setFechaCertificacion(value.toDate());
            return true;
        }
        else
        {
            return false;
        }
    }
    );

    setField(2, "Estado",
             [&] (EntityBasePtr entity, int role) -> QVariant
    {
        CertificacionPtr c = cast(entity);
        QVariant v;
        switch (role)
        {
        case Qt::DisplayRole:
        {
            switch (c->certificacionStatus())
            {
            case Certificacion::CertificacionStatus::Preparacion:
                v = "En Preparación";
                break;
            case Certificacion::CertificacionStatus::Emitido:
                v = "Emitido";
                break;
            default:
                v = QVariant();
                break;
            }
        }
            break;
        case Qt::EditRole:
            v = static_cast<int>(c->certificacionStatus());
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
            CertificacionPtr c = cast(e);
            c->setCertificacionStatus(static_cast<Certificacion::CertificacionStatus>(value.toInt()));
        }
    });
}


QString CertificacionesModel::_getSQLRead() const
{
    return "select * from certificaciones;";
}

int CertificacionesModel::_loadEntity(QSqlRecord record)
{
    int id = record.value(record.indexOf("id")).toInt();
    QDate fechaCertificacion = record.value(record.indexOf("fechaCertificacion")).toDate();
    Certificacion::CertificacionStatus certStatus =
            static_cast<Certificacion::CertificacionStatus>(record.value(record.indexOf("certificacionStatus")).toInt());
    EntityBasePtr entity =  CertificacionPtr::create(id, fechaCertificacion, certStatus);
    addEntity(entity);
    return id;
}

EntityBasePtr CertificacionesModel::internalCreateEntity(int assignedId)
{
    return CertificacionPtr::create(assignedId);
}


void CertificacionesModel::editEntity(int row)
{
    dlgEditCertificacion dlg(this, row);
    dlg.setMinDate(maxDateRealizada());
    dlg.exec();
}

CertificacionPtr CertificacionesModel::cast(EntityBasePtr entity)
{
    return qSharedPointerDynamicCast<Certificacion>(entity);
}

int CertificacionesModel::idCertificacionProxima(const QDate &fecha, bool onlyEnPreparacion) const
{
    CertificacionPtr c;
    foreach (int id, ids())
    {
        EntityBasePtr e = getItem(id);
        CertificacionPtr cert = qSharedPointerDynamicCast<Certificacion>(e);

        bool usarFecha = onlyEnPreparacion ?
                    (cert->certificacionStatus() == Certificacion::CertificacionStatus::Preparacion) :
                    true;

        if (usarFecha && (fecha < cert->fechaCertificacion()))
        {
            if (c.isNull())
            {
                c = cert;
            }
            else
            {
                if (cert->fechaCertificacion() < c->fechaCertificacion())
                {
                    c = cert;
                }
            }
        }
    }
    return c.isNull() ? -1 : c->id();
}

QDate CertificacionesModel::maxDateRealizada()
{
    QSet<int> ids = this->ids();

    QDate date = QDate::fromJulianDay(0);

    foreach (int id, ids)
    {
        CertificacionPtr c = cast(getItem(id));
        if (date < c->fechaCertificacion())
        {
            date = c->fechaCertificacion();
        }
    }
    return date;
}
