#include "unit.h"
#include <QVariant>


Unit::Unit(int id, const QString &name, const QString &description, QObject *parent) : EntityBase(id, parent)
{
    _name = name;
    _description = description;
}

bool Unit::internalSetData(const int column, const QVariant &value, int role)
{
    switch (column)
    {
    case 0:
        _name = value.toString();
        return true;
        break;
    case 1:
        _description = value.toString();
        return true;
        break;
    default:
        break;
    }
    return false;
}

QVariant Unit::internalData(const int column, int role) const
{
    switch (column)
    {
    case 0:
        return _name;
        break;
    case 1:
        return _description;
        break;
    default:
        return QVariant();
        break;
    }
}

QSqlQuery* Unit::getQuery(QSqlDatabase &database)
{
    QSqlQuery *query;
    switch (status())
    {
    case EntityStatus::added:
    {
        query = new QSqlQuery(database);
        query->prepare("INSERT INTO units (nombre, descripcion) VALUES (:nombre, :descripcion);");
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
