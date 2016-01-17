#include "proveedor.h"
#include <QVariant>


Proveedor::Proveedor(int id) : EntityBase(id, true)
{

}

Proveedor::Proveedor(int id, const QString &name, const QString &contacto,
                     const QString &email, const QString &telefono, const QString &direccion) : EntityBase(id)
{
    _name = name;
    _contacto = contacto;
    _email = email;
    _telefono = telefono;
    _direccion = direccion;
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
        _contacto = value.toString();
        return true;
        break;
    case 3:
        _email = value.toString();
        return true;
        break;
    case 4:
        _telefono = value.toString();
        return true;
        break;
    case 5:
        _direccion = value.toString();
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
        return _contacto;
        break;
    case 3:
        return _email;
        break;
    case 4:
        return _telefono;
        break;
    case 5:
        return _direccion;
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
        query->prepare("INSERT INTO proveedores (name, contacto, email, telefono, direccion) VALUES (:name, :contacto, :email, :telefono, :direccion);");
        query->bindValue(":name", _name);
        query->bindValue(":contacto", _contacto);
        query->bindValue(":email", _email);
        query->bindValue(":telefono", _telefono);
        query->bindValue(":direccion", _direccion);
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
        query->prepare("UPDATE proveedores SET name = :name, contacto = :contacto, email = :email, telefono = :telefono, direccion = :direccion WHERE id = :id;");
        query->bindValue(":name", _name);
        query->bindValue(":contacto", _contacto);
        query->bindValue(":email", _email);
        query->bindValue(":telefono", _telefono);
        query->bindValue(":direccion", _direccion);
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

QString Proveedor::contacto() const
{
    return _contacto;
}

QString Proveedor::email() const
{
    return _email;
}

QString Proveedor::telefono() const
{
    return _telefono;
}

QString Proveedor::direccion() const
{
    return _direccion;
}
