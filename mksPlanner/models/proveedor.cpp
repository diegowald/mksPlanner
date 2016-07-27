#include "proveedor.h"
#include <QVariant>
#include "globalcontainer.h"
#include "models/rubrosproveedoresmodel.h"

Proveedor::Proveedor(int id) : EntityBase(id, true)
{

}

Proveedor::Proveedor(int id, const QString &name, const QString &contacto,
                     const QString &email, const QString &telefono, const QString &direccion,
                     const QString &web) : EntityBase(id)
{
    _name = name;
    _contacto = contacto;
    _email = email;
    _telefono = telefono;
    _direccion = direccion;
    _web = web;
}

/*bool Proveedor::internalSetData(const int column, const QVariant &value, int role)
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
}*/

QSqlQuery* Proveedor::getQuery(QSqlDatabase &database)
{
    QSqlQuery *query = NULL;
    switch (status())
    {
    case EntityStatus::added:
    {
        query = new QSqlQuery(database);
        query->prepare("INSERT INTO proveedores (id, name, contacto, email, telefono, direccion, web) VALUES (:id, :name, :contacto, :email, :telefono, :direccion, :web);");
        query->bindValue(":id", id());
        query->bindValue(":name", _name);
        query->bindValue(":contacto", _contacto);
        query->bindValue(":email", _email);
        query->bindValue(":telefono", _telefono);
        query->bindValue(":direccion", _direccion);
        query->bindValue(":web", _web);
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
        query->prepare("UPDATE proveedores SET name = :name, contacto = :contacto, email = :email, telefono = :telefono, direccion = :direccion, web = :web WHERE id = :id;");
        query->bindValue(":name", _name);
        query->bindValue(":contacto", _contacto);
        query->bindValue(":email", _email);
        query->bindValue(":telefono", _telefono);
        query->bindValue(":direccion", _direccion);
        query->bindValue(":id", id());
        query->bindValue(":web", _web);
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

QString Proveedor::web() const
{
    return _web;
}

QString Proveedor::toDebugString()
{
    return QString("id: %1, name: %2, contacto: %3, email: %4, telefono: %5, direccion: %6")
            .arg(id()).arg(_name).arg(_contacto).arg(_email).arg(_telefono).arg(_direccion);
}


void Proveedor::setName(const QString &value)
{
    _name = value;
    updateStatus();
}

void Proveedor::setContacto(const QString &value)
{
    _contacto = value;
    updateStatus();
}

void Proveedor::setEMail(const QString &value)
{
    _email = value;
    updateStatus();
}

void Proveedor::setTelefono(const QString &value)
{
    _telefono = value;
    updateStatus();
}

void Proveedor::setDireccion(const QString &value)
{
    _direccion = value;
    updateStatus();
}

void Proveedor::setWeb(const QString &value)
{
    _web = value;
    updateStatus();
}

bool Proveedor::proveeRubro(int idRubro)
{
    RubrosProveedoresModel *model = qobject_cast<RubrosProveedoresModel*>(GlobalContainer::instance().library()->model(Tables::RubrosProveedores));
    EntityBasePtr entity = model->getItemBy(idRubro, id());
    return !entity.isNull();
}
