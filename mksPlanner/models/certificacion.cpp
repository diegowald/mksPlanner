#include "certificacion.h"
#include <QSqlQuery>
#include <QVariant>
#include "globalcontainer.h"

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

QDate Certificacion::fechaInicioCertificacion() const
{
    QList<int> ids = GlobalContainer::instance().projectLibrary(_idProyecto);
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
