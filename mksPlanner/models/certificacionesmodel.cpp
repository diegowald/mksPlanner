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
            cast(entity)->setFechaCertificacion(value.toDateTime());
            return true;
        }
        else
        {
            return false;
        }
    }
    );
}


QString CertificacionesModel::_getSQLRead() const
{
    return "select * from certificaciones;";
}

int CertificacionesModel::_loadEntity(QSqlRecord record)
{
    int id = record.value(record.indexOf("id")).toInt();
    QDateTime fechaCertificacion = record.value(record.indexOf("fechaCertificacion")).toDateTime();

    EntityBasePtr entity = CertificacionPtr::create(id, fechaCertificacion);
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
    dlg.exec();
}

CertificacionPtr CertificacionesModel::cast(EntityBasePtr entity)
{
    return qSharedPointerDynamicCast<Certificacion>(entity);
}

int CertificacionesModel::idCertificacionProxima(const QDateTime &fecha) const
{
    CertificacionPtr c;
    foreach (int id, ids())
    {
        EntityBasePtr e = getItem(id);
        CertificacionPtr cert = qSharedPointerDynamicCast<Certificacion>(e);
        if (fecha < cert->fechaCertificacion())
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
