#include "componentematerial.h"
#include <QVariant>

ComponenteMaterial::ComponenteMaterial() : EntityBase()
{
    _idMaterial = -1;
    _cantidad = -1;
    _idMaterialPadre = -1;
}

ComponenteMaterial::ComponenteMaterial(int id, int idMaterialPadre, int idMaterial, double cantidad) : EntityBase(id)
{
    _idMaterial = idMaterial;
    _cantidad = cantidad;
    _idMaterialPadre = idMaterialPadre;
}

bool ComponenteMaterial::internalSetData(const int column, const QVariant &value, int role)
{
    switch (column)
    {
    case 1:
        _idMaterial = value.toInt();
        return true;
        break;
    case 2:
        _cantidad = value.toDouble();
        return true;
        break;
    default:
        break;
    }
    return false;
}

QVariant ComponenteMaterial::internalData(const int column, int role) const
{
    switch (column)
    {
    case 0:
        return id();
        break;
    case 1:
        return _idMaterial;
        break;
    case 2:
        return _cantidad;
        break;
    default:
        return QVariant();
        break;
    }
}

QSqlQuery* ComponenteMaterial::getQuery(QSqlDatabase &database)
{
    QSqlQuery *query;
    switch (status())
    {
    case EntityStatus::added:
    {
        query = new QSqlQuery(database);
        query->prepare("INSERT INTO componentesMateriales (idMaterialPadre, idMaterial, cantidad) VALUES (:idMaterialPadre, :idMaterial, :cantidad);");
        query->bindValue(":idMaterialPadre", _idMaterialPadre);
        query->bindValue(":idMaterial", _idMaterial);
        query->bindValue(":cantidad", _cantidad);
        break;
    }
    case EntityStatus::deleted:
    {
        query = new QSqlQuery(database);
        query->prepare("DELETE FROM componentesMateriales WHERE id = :id;");
        query->bindValue(":id", id());
        break;
    }
    case EntityStatus::modified:
    {
        query = new QSqlQuery(database);
        query->prepare("UPDATE componentesMateriales SET idMaterialPadre = :idMaterialPadre, idMaterial = :idMaterial, cantidad = :cantidad WHERE id = :id;");
        query->bindValue(":idMaterialPadre", _idMaterialPadre);
        query->bindValue(":idMaterial", _idMaterial);
        query->bindValue(":cantidad", _cantidad);
        query->bindValue(":id", id());
        break;
    }
    case EntityStatus::unchanged:
        query = NULL;
        break;
    }
    return query;
}
