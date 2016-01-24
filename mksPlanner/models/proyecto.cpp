#include "proyecto.h"
#include <QVariant>


Proyecto::Proyecto(int id, const QString &propietario, const QString &direccion, const QString &email, const QString &telefono)
    :EntityBase(id)
{
    _propietario = propietario;
    _direccion = direccion;
    _email = email;
    _telefono = telefono;
}


Proyecto::Proyecto(int id) : EntityBase(id, true)
{

}


bool Proyecto::internalSetData(const int column, const QVariant &value, int role)
{
    switch (column)
    {
    case 0:
        break;
    case 1:
        _propietario = value.toString();
        return true;
        break;
    case 2:
        _direccion = value.toString();
        return true;
        break;
    case 3:
    {
        _email = value.toString();
        return true;
        break;
    }
    case 4:
    {
        _telefono = value.toString();
        return true;
        break;
    }
    default:
        break;
    }
    return false;
}

/*QVariant Proyecto::internalData(const int column, int role) const
{
    switch (column)
    {
    case 0:
        return id();
        break;
    case 1:
    {
        return _propietario;
        break;
    }
    case 2:
    {
        return _direccion;
        break;
    }
    case 3:
    {
        return _email;
        break;
    }
    case 4:
    {
        return _telefono;
        break;
    }
    default:
        return QVariant();
        break;
    }
}*/

QSqlQuery* Proyecto::getQuery(QSqlDatabase &database)
{
    QSqlQuery *query;
    switch (status())
    {
    case EntityStatus::added:
    {
        query = new QSqlQuery(database);
        query->prepare("INSERT INTO proyectos (propietario, direccion, email, telefono) VALUES (:propietario, :direccion, :email, :telefono);");
        query->bindValue(":propietario", _propietario);
        query->bindValue(":direccion", _direccion);
        query->bindValue(":email", _email);
        query->bindValue(":telefono", _telefono);
        break;
    }
    case EntityStatus::deleted:
    {
        query = new QSqlQuery(database);
        query->prepare("DELETE FROM proyectoss WHERE id = :id;");
        query->bindValue(":id", id());
        break;
    }
    case EntityStatus::modified:
    {
        query = new QSqlQuery(database);
        query->prepare("UPDATE proyectos SET propietario = :propietario, direccion = :direccion, email = :email, telefono = :telefono WHERE id = :id;");
        query->bindValue(":propietario", _propietario);
        query->bindValue(":direccion", _direccion);
        query->bindValue(":email", _email);
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

QString Proyecto::toDebugString()
{
    return QString("id: %1, propietario: %2, direccion: %3, email: %4, telefono: %5")
            .arg(id()).arg(_propietario).arg(_direccion).arg(_email).arg(_telefono);
}


QString Proyecto::propietario()
{
    return _propietario;
}

QString Proyecto::direccion()
{
    return _direccion;
}

QString Proyecto::email()
{
    return _email;
}

QString Proyecto::telefono()
{
    return _telefono;
}
