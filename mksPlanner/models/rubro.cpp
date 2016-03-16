#include "rubro.h"
#include <QVariant>

Rubro::Rubro(int id) : EntityBase(id, true)
{
    _name = "";
    _description = "";
    _isTask = false;
}


Rubro::Rubro(int id, const QString &name, const QString &description, bool isTask) : EntityBase(id)
{
    _name = name;
    _description = description;
    _isTask = isTask;
}

/*bool Rubro::internalSetData(const int column, const QVariant &value, int role)
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
    case 3:
        _isTask = value.toBool();
        return true;
        break;
    default:
        break;
    }
    return false;
}*/

QString Rubro::toDebugString()
{
    return QString("id: %1, name: %2").arg(id()).arg(_name);
}

QSqlQuery* Rubro::getQuery(QSqlDatabase &database)
{
    QSqlQuery *query = NULL;
    switch (status())
    {
    case EntityStatus::added:
    {
        query = new QSqlQuery(database);
        query->prepare("INSERT INTO rubros (nombre, descripcion, isTask) VALUES (:nombre, :descripcion, :isTask);");
        query->bindValue(":nombre", _name);
        query->bindValue(":descripcion", _description);
        query->bindValue(":isTask", _isTask);
        break;
    }
    case EntityStatus::deleted:
    {
        query = new QSqlQuery(database);
        query->prepare("DELETE FROM rubros WHERE id = :id;");
        query->bindValue(":id", id());
        break;
    }
    case EntityStatus::modified:
    {
        query = new QSqlQuery(database);
        query->prepare("UPDATE rubros SET nombre = :nombre, descripcion = :descripcion, isTask = :isTask WHERE id = :id;");
        query->bindValue(":nombre", _name);
        query->bindValue(":descripcion", _description);
        query->bindValue(":isTask", _isTask);
        query->bindValue(":id", id());
        break;
    }
    case EntityStatus::unchanged:
        query = NULL;
        break;
    }
    return query;
}

QString Rubro::name() const
{
    return _name;
}

QString Rubro::description() const
{
    return _description;
}

bool Rubro::isTask() const
{
    return _isTask;
}


void Rubro::setName(const QString &value)
{
    _name = value;
    updateStatus();
}

void Rubro::setDescripcion(const QString &value)
{
    _description = value;
    updateStatus();
}

void Rubro::setIsTask(bool value)
{
    _isTask = value;
    updateStatus();
}
