#include "material.h"
#include <QVariant>
#include "globalcontainer.h"
#include "models/unit.h"


Material::Material(int id, const QString &name, const QString &description, int idUnit) : EntityBase(id)
{
    _name = name;
    _description = description;
    _idUnit = idUnit;
}

Material::Material(int id):EntityBase(id, true)
{
    _name = "";
    _description = "";
    _idUnit = -1;
}

bool Material::internalSetData(const int column, const QVariant &value, int role)
{
    bool result = false;
    switch (column)
    {
    case 1:
        _name = value.toString();
        result = true;
        break;
    case 2:
        _description = value.toString();
        result = true;
        break;
    case 3:
        _idUnit = value.toInt();
        result = true;
        break;
    default:
        break;
    }
    return result;
}

QVariant Material::internalData(const int column, int role) const
{
    QVariant result;
    switch (column)
    {
    case 0:
        result = id();
        break;
    case 1:
        result = _name;
        break;
    case 2:
        result = _description;
        break;
    case 3:
        if (!unit().isNull())
        {
            result = qSharedPointerDynamicCast<Unit>(unit())->name();
        }
        break;
    case 4:
        result = _isUsableMaterial;
        break;
    case 5:
        result = _isTask;
        break;
    default:
        break;
    }
    return result;
}

QSqlQuery* Material::getQuery(QSqlDatabase &database)
{
    QSqlQuery *query;
    switch (status())
    {
    case EntityStatus::added:
    {
        query = new QSqlQuery(database);
        query->prepare("INSERT INTO materiales (name, description, idUnit) VALUES (:nombre, :descripcion, :idUnit);");
        query->bindValue(":nombre", _name);
        query->bindValue(":descripcion", _description);
        query->bindValue(":idUnit", _idUnit);
        break;
    }
    case EntityStatus::deleted:
    {
        query = new QSqlQuery(database);
        query->prepare("DELETE FROM materiales WHERE id = :id;");
        query->bindValue(":id", id());
        break;
    }
    case EntityStatus::modified:
    {
        query = new QSqlQuery(database);
        query->prepare("UPDATE materiales SET name = :nombre, description = :descripcion, idUnit = :idUnit WHERE id = :id;");
        query->bindValue(":nombre", _name);
        query->bindValue(":descripcion", _description);
        query->bindValue(":idUnit", _idUnit);
        query->bindValue(":id", id());
        break;
    }
    case EntityStatus::unchanged:
        query = NULL;
        break;
    }
    return query;
}

QString Material::name() const
{
    return _name;
}

QString Material::desription() const
{
    return _description;
}

int Material::idUnit() const
{
    return _idUnit;
}

EntityBasePtr Material::unit() const
{
    return GlobalContainer::instance().materialLibrary()->model("unidades")->getItem(_idUnit);
}
