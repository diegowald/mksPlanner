#include "certificado.h"
#include <QSqlQuery>
#include <QVariant>
#include "globalcontainer.h"
#include "models/proyecto.h"
#include "models/proveedor.h"

Certificado::Certificado(int id, int idCertificacion, int idProveedor,
                         StatusCertificado statusCertificado,
                         const QDate &fechaEmision,
                         const QDate &desde, const QDate &hasta) : EntityBase(id)
{
    _idCertificacion = idCertificacion;
    _idProveedor = idProveedor;
    _statusCertificado = statusCertificado;
    _fechaEmision = fechaEmision;
    _desde = desde;
    _hasta = hasta;
}

Certificado::Certificado(int id) : EntityBase(id, true)
{
    _idCertificacion = -1;
    _idProveedor = -1;
    _statusCertificado = StatusCertificado::Emitido;
}

QSqlQuery* Certificado::getQuery(QSqlDatabase &database)
{
    QSqlQuery *query = NULL;
    switch (status())
    {
    case EntityStatus::added:
    {
        query = new QSqlQuery(database);
        query->prepare("INSERT INTO certificados (id, idCertificacion, idProveedor, "
                       " statusCertificado, fechaEmision, desde, hasta) VALUES (:id, :idCertificacion, :idProveedor, "
                       ":statusCertificado, :fechaEmision, :desde, :hasta);");
        query->bindValue(":id", id());
        query->bindValue(":idCertificacion", _idCertificacion);
        query->bindValue(":idProveedor", _idProveedor);
        query->bindValue(":statusCertificado", static_cast<int>(_statusCertificado));
        query->bindValue(":fechaEmision", _fechaEmision);
        query->bindValue(":desde", _desde);
        query->bindValue(":hasta", _hasta);

        break;
    }
    case EntityStatus::deleted:
    {
        query = new QSqlQuery(database);
        query->prepare("DELETE FROM certificados WHERE id = :id;");
        query->bindValue(":id", id());
        break;
    }
    case EntityStatus::modified:
    {
        query = new QSqlQuery(database);
        query->prepare("UPDATE certificados SET idCertificacion = :idCertificacion, idProveedor = :idProveedor, "
                       " statusCertificado = :statusCertificado, fechaEmision = :fechaEmision, "
                       " desde = :desde, hasta = :hasta "
                       " WHERE id = :id;");
        query->bindValue(":idCertificacion", _idCertificacion);
        query->bindValue(":idProveedor", _idProveedor);
        query->bindValue(":statusCertificado", static_cast<int>(_statusCertificado));
        query->bindValue(":fechaEmision", _fechaEmision);
        query->bindValue(":desde", _desde);
        query->bindValue(":hasta", _hasta);

        query->bindValue(":id", id());
        break;
    }
    case EntityStatus::unchanged:
        query = NULL;
        break;
    }
    return query;
}

QString Certificado::toDebugString()
{
    return QString("id: %1, idCertificacion: %2, idCertificado: %3, isClient: %4")
            .arg(id()).arg(_idCertificacion)
            .arg(_idProveedor).arg(isClientCertificate());
}

int Certificado::idCertificacion() const
{
    return _idCertificacion;
}

int Certificado::idProveedor() const
{
    return _idProveedor;
}

bool Certificado::isClientCertificate() const
{
    return (_idProveedor == 1);
}

Certificado::StatusCertificado Certificado::statusCertificado() const
{
    return _statusCertificado;
}

QDate Certificado::fechaEmision() const
{
    return _fechaEmision;
}

QDate Certificado::desde() const
{
    return _desde;
}

QDate Certificado::hasta() const
{
    return _hasta;
}

QString Certificado::cliente() const
{
    EntityBasePtr entity = GlobalContainer::instance().projectLibrary(_idProyecto)->model(Tables::Proyectos)->getItem(0);
    ProyectoPtr p = qSharedPointerDynamicCast<Proyecto>(entity);
    return p.isNull() ? "" : p->propietario();
}

QString Certificado::proveedor() const
{
    EntityBasePtr entity = GlobalContainer::instance().library()->model(Tables::Proveedores)->getItem(_idProveedor);
    ProveedorPtr p = qSharedPointerDynamicCast<Proveedor>(entity);
    return p.isNull() ? "" : p->name();
}

QString Certificado::nroCertificado() const
{
    return QString("%1-%2").arg(_idCertificacion).arg(id());
}

void Certificado::setIdCertificacion(int value)
{
    _idCertificacion = value;
    updateStatus();
}

void Certificado::setIdProveedor(int value)
{
    _idProveedor = value;
    updateStatus();
}

void Certificado::setStatusCertificado(StatusCertificado value)
{
    _statusCertificado = value;
    updateStatus();
}

void Certificado::setFechaEmision(const QDate& value)
{
    _fechaEmision = value;
    updateStatus();
}

void Certificado::setDesde(const QDate &value)
{
    _desde = value;
    updateStatus();
}

void Certificado::setHasta(const QDate &value)
{
    _hasta = value;
    updateStatus();
}

void Certificado::setIdProyecto(int idProyecto)
{
    _idProyecto = idProyecto;
}
