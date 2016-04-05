#include "unit.h"
#include <QVariant>


Unit::Unit(int id, const QString &name, const QString &description) : EntityBase(id)
{
    _name = name;
    _description = description;
}

Unit::Unit(int id) : EntityBase(id, true)
{
    _name = "";
    _description = "";
}

/*bool Unit::internalSetData(const int column, const QVariant &value, int role)
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
        _description = value.toString();
        return true;
        break;
    default:
        break;
    }
    return false;
}*/

QSqlQuery* Unit::getQuery(QSqlDatabase &database)
{
    QSqlQuery *query = NULL;
    switch (status())
    {
    case EntityStatus::added:
    {
        query = new QSqlQuery(database);
        query->prepare("INSERT INTO units (id, nombre, descripcion) VALUES (:id, :nombre, :descripcion);");
        query->bindValue(":id", id());
        query->bindValue(":nombre", _name);
        query->bindValue(":descripcion", _description);
        break;
    }
    case EntityStatus::deleted:
    {
        query = new QSqlQuery(database);
        query->prepare("DELETE FROM units WHERE id = :id;");
        query->bindValue(":id", id());
        break;
    }
    case EntityStatus::modified:
    {
        query = new QSqlQuery(database);
        query->prepare("UPDATE units SET nombre = :nombre, descripcion = :descripcion WHERE id = :id;");
        query->bindValue(":nombre", _name);
        query->bindValue(":descripcion", _description);
        query->bindValue(":id", id());
        break;
    }
    case EntityStatus::unchanged:
        query = NULL;
        break;
    }
    return query;
}

QString Unit::name() const
{
    return _name;
}

QString Unit::description() const
{
    return _description;
}

QString Unit::toDebugString()
{
    return QString("id: %1, name: %2").arg(id()).arg(_name);
}

void Unit::setName(const QString &value)
{
    _name = value;
    updateStatus();
}

void Unit::setDescripcion(const QString &value)
{
    _description = value;
    updateStatus();
}
