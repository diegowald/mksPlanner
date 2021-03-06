#include "certificacion.h"
#include <QSqlQuery>
#include <QVariant>
#include "globalcontainer.h"
#include "models/certificacionesmodel.h"
#include "persistance/materialslibrary.h"
#include "models/tareacertificadosmodel.h"
#include "models/executiontask.h"

Certificacion::Certificacion(int id, const QDate &fechaCertificacion, CertificacionStatus certificacionStatus) : EntityBase(id)
{
    _fechaCertificacion = fechaCertificacion;
    _certificacionStatus = certificacionStatus;
}

Certificacion::Certificacion(int id) : EntityBase(id, true)
{
    _fechaCertificacion = QDate::currentDate();
    _certificacionStatus = CertificacionStatus::Preparacion;
}


QSqlQuery* Certificacion::getQuery(QSqlDatabase &database)
{
    QSqlQuery *query = NULL;
    switch (status())
    {
    case EntityStatus::added:
    {
        query = new QSqlQuery(database);
        query->prepare("INSERT INTO certificaciones (id, fechaCertificacion, certificacionStatus) VALUES (:id, :fechaCertificacion, :certificacionStatus);");
        query->bindValue(":id", id());
        query->bindValue(":fechaCertificacion", _fechaCertificacion);
        query->bindValue(":certificacionStatus", static_cast<int>(_certificacionStatus));
        break;
    }
    case EntityStatus::deleted:
    {
        query = new QSqlQuery(database);
        query->prepare("DELETE FROM certificaciones WHERE id = :id;");
        query->bindValue(":id", id());
        break;
    }
    case EntityStatus::modified:
    {
        query = new QSqlQuery(database);
        query->prepare("UPDATE certificaciones SET fechaCertificacion = :fechaCertificacion, certificacionStatus = :certificacionStatus WHERE id = :id;");
        query->bindValue(":fechaCertificacion", _fechaCertificacion);
        query->bindValue(":certificacionStatus", static_cast<int>(_certificacionStatus));
        query->bindValue(":id", id());
        break;
    }
    case EntityStatus::unchanged:
        query = NULL;
        break;
    }
    return query;
}

QString Certificacion::toDebugString()
{
    return QString("id: %1, fecha: %2").arg(id()).arg(_fechaCertificacion.toString());
}

QDate Certificacion::fechaCertificacion() const
{
    return _fechaCertificacion;
}

QDate Certificacion::fechaInicioCertificacion()
{
    QDate fechaInicio = fechaCertificacion();
    CertificacionesModel *m = static_cast<CertificacionesModel*>(GlobalContainer::instance().projectLibrary(_idProyecto)->model(Tables::Certificaciones));

    QSet<int> ids = m->ids();
    bool fechaInicioDeCertificacionAnterior = false;
    foreach(int idCert, ids.values())
    {
        if (idCert != id())
        {
            CertificacionPtr c = m->cast(m->getItem(idCert));
            if (c->fechaCertificacion() < _fechaCertificacion)
            {
                if (fechaInicio < c->fechaCertificacion())
                {
                    fechaInicio = c->fechaCertificacion();
                    fechaInicioDeCertificacionAnterior = true;
                }
            }
        }
    }

    if (!fechaInicioDeCertificacionAnterior)
    {
        fechaInicio = calcularFechaInicioPrimerTarea();
    }

    return fechaInicio;
}

QDate Certificacion::calcularFechaInicioPrimerTarea() const
{
    QDate fechaInicio = fechaCertificacion();

    TareaCertificadosModel *tcModel = qobject_cast<TareaCertificadosModel*>(GlobalContainer::instance().projectLibrary(_idProyecto)->model(Tables::TareaCertificados));
    int rowCount = tcModel->rowCount(QModelIndex());
    for (int i = 0; i < rowCount; ++i)
    {
        EntityBasePtr e = tcModel->getItemByRowid(i);
        TareaCertificadoPtr tc = qSharedPointerDynamicCast<TareaCertificado>(e);
        ExecutionTaskPtr et = qSharedPointerDynamicCast<ExecutionTask>(tc->tareaEjecucion());
        fechaInicio = (et->fechaRealInicio().date() < fechaInicio) ? et->fechaRealInicio().date() : fechaInicio;
    }

    return fechaInicio;
}

void Certificacion::setFechaCertificacion(const QDate &value)
{
    _fechaCertificacion = value;
    updateStatus();
}

Certificacion::CertificacionStatus Certificacion::certificacionStatus() const
{
    return _certificacionStatus;
}

void Certificacion::setCertificacionStatus(CertificacionStatus value)
{
    _certificacionStatus = value;
    updateStatus();
}


void Certificacion::setIdProyecto(int idProyecto)
{
    _idProyecto = idProyecto;
}
