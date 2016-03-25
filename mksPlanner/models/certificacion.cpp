#include "certificacion.h"
#include <QSqlQuery>
#include <QVariant>


Certificacion::Certificacion(int id, const QDateTime &fechaCertificacion) : EntityBase(id)
{
    _fechaCertificacion = fechaCertificacion;
}

Certificacion::Certificacion(int id) : EntityBase(id)
{
    _fechaCertificacion = QDateTime::currentDateTime();
}


QSqlQuery* Certificacion::getQuery(QSqlDatabase &database)
{
    QSqlQuery *query = NULL;
    switch (status())
    {
    case EntityStatus::added:
    {
        query = new QSqlQuery(database);
        query->prepare("INSERT INTO certificaciones (id, fechaCertificacion) VALUES (:id, :fechaCertificacion);");
        query->bindValue(":id", id());
        query->bindValue(":fechaCertificacion", _fechaCertificacion);
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
        query->prepare("UPDATE cerificaciones SET fechaCertificacion = :fechaCertificacion WHERE id = :id;");
        query->bindValue(":fechaCertificacion", _fechaCertificacion);
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

QDateTime Certificacion::fechaCertificacion() const
{
    return _fechaCertificacion;
}


void Certificacion::setFechaCertificacion(const QDateTime &value)
{
    _fechaCertificacion = value;
    updateStatus();
}
