#include "proveedor.h"
#include <QVariant>


Proveedor::Proveedor(int id) : EntityBase(id, true)
{

}

Proveedor::Proveedor(int id, const QString &name, const QString &telefono) : EntityBase(id)
{
    _name = name;
    _telefono = telefono;
}

bool Proveedor::internalSetData(const int column, const QVariant &value, int role)
{
    switch (column)
    {
    case 0:
        break;
    case 1:
        _name = value.toString();
        return true;
        break;
    case 2:
        _telefono = value.toString();
        return true;
        break;
    default:
        break;
    }
    return false;
}

QVariant Proveedor::internalData(const int column, int role) const
{
    switch (column)
    {
    case 0:
        return id();
        break;
    case 1:
        return _name;
        break;
    case 2:
        return _telefono;
        break;
    default:
        return QVariant();
        break;
    }
}

QSqlQuery* Proveedor::getQuery(QSqlDatabase &database)
{
    QSqlQuery *query;
    switch (status())
    {
    case EntityStatus::added:
    {
        query = new QSqlQuery(database);
        query->prepare("INSERT INTO proveedores (name, telefono) VALUES (:name, :telefono);");
        query->bindValue(":name", _name);
        query->bindValue(":telefono", _telefono);
        break;
    }
    case EntityStatus::deleted:
    {
        query = new QSqlQuery(database);
        query->prepare("DELETE FROM proveedores WHERE id = :id;");
        query->bindValue(":id", id());
        break;
    }
    case EntityStatus::modified:
    {
        query = new QSqlQuery(database);
        query->prepare("UPDATE proveedores SET name = :name, telefono = :telefono WHERE id = :id;");
        query->bindValue(":name", _name);
        query->bindValue(":telefono", _telefono);
        query->bindValue(":id", id());
        break;
    }
    case EntityStatus::unchanged:
        query = NULL;
        break;
    }
    return query;
}

QString Proveedor::name() const
{
    return _name;
}

QString Proveedor::telefono() const
{
    return _telefono;
}
