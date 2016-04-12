#include "tareascertificado.h"
#include <QSqlQuery>
#include <QVariant>
#include "globalcontainer.h"
#include "models/proveedor.h"

TareaCertificado::TareaCertificado(int id, int idCertificacion,
                                   int idProveedor, int idTareaEjecucion) : EntityBase(id)
{
    _idCertificacion = idCertificacion;
    _idProveedor = idProveedor;
    _idTareaEjecucion = idTareaEjecucion;
}

TareaCertificado::TareaCertificado(int id) : EntityBase(id)
{
    _idCertificacion = -1;
    _idProveedor = -1;
    _idTareaEjecucion = -1;
}

QSqlQuery* TareaCertificado::getQuery(QSqlDatabase &database)
{
    QSqlQuery *query = NULL;
    switch (status())
    {
    case EntityStatus::added:
    {
        query = new QSqlQuery(database);
        query->prepare("INSERT INTO tareasCertificados (id, idCertificacion, idProveedor, idTareaEjecucion) "
                       " VALUES (:id, :idCertificacion, :idProveedor, :iTareaEjecucion);");
        query->bindValue(":id", id());
        query->bindValue(":idCertificacion", _idCertificacion);
        query->bindValue(":idProveedor", _idProveedor);
        query->bindValue(":idTareaEjecucion", _idTareaEjecucion);

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
        query->prepare("UPDATE cerificaciones SET idCertificacion = :idCertificacion, idProveedor = :idProveedor, idTareaEjecucion = :idTareaEjecucion "
                       " WHERE id = :id;");
        query->bindValue(":idCertificacion", _idCertificacion);
        query->bindValue(":idProveedor", _idProveedor);
        query->bindValue(":idTareaEjecucion", _idTareaEjecucion);

        query->bindValue(":id", id());
        break;
    }
    case EntityStatus::unchanged:
        query = NULL;
        break;
    }
    return query;
}

QString TareaCertificado::toDebugString()
{
    return QString("id: %1, idCertificacion: %2, idCertificado: %3, idTareaEjecucion: %4")
            .arg(id()).arg(_idCertificacion)
            .arg(_idProveedor).arg(_idTareaEjecucion);
}

int TareaCertificado::idCertificacion() const
{
    return _idCertificacion;
}

int TareaCertificado::idProveedor() const
{
    return _idProveedor;
}

int TareaCertificado::idTareaEjecucion() const
{
    return _idTareaEjecucion;
}

QString TareaCertificado::proveedor() const
{
    EntityBasePtr entity = GlobalContainer::instance().library()->model(Tables::Proveedores)->getItem(_idProveedor);
    ProveedorPtr p = qSharedPointerDynamicCast<Proveedor>(entity);
    return p.isNull() ? "" : p->name();
}

void TareaCertificado::setIdCertificacion(int value)
{
    _idCertificacion = value;
    updateStatus();
}

void TareaCertificado::setIdProveedor(int value)
{
    _idProveedor = value;
    updateStatus();
}

void TareaCertificado::setIdTareaEjecucion(int value)
{
    _idTareaEjecucion = value;
    updateStatus();
}

void TareaCertificado::setIdProyecto(int idProyecto)
{
    _idProyecto = idProyecto;
}

EntityBasePtr TareaCertificado::tareaEjecucion() const
{
    EntityBasePtr entity = GlobalContainer::instance().projectLibrary(_idProyecto)->model(Tables::ExecutionTasks)->getItem(_idTareaEjecucion);
    return entity;
}
