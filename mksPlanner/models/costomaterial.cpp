#include "costomaterial.h"
#include <QVariant>
#include "globalcontainer.h"
#include "models/material.h"

CostoMaterial::CostoMaterial(int id) : EntityBase(id, true)
{
    _idMaterial = -1;
    _costo = 0.0;
    _desde = QDate::currentDate();
}

CostoMaterial::CostoMaterial(int id, int idMaterial, double costo, double precio, QDate desde) : EntityBase(id)
{
    _idMaterial = idMaterial;
    _costo = costo;
    _precio = precio;
    _desde = desde;
}


void CostoMaterial::setIdMaterial(int id)
{
    _idMaterial = id;
    updateStatus();
}

void CostoMaterial::setCosto(double value)
{
    _costo = value;
    updateStatus();
}

void CostoMaterial::setPrecio(double value)
{
    _precio = value;
    updateStatus();
}

void CostoMaterial::setDesde(QDate &date)
{
    _desde = date;
    updateStatus(EntityStatus::modified);
}

QSqlQuery* CostoMaterial::getQuery(QSqlDatabase &database)
{
    QSqlQuery *query = NULL;
    switch (status())
    {
    case EntityStatus::added:
    {
        query = new QSqlQuery(database);
        query->prepare("INSERT INTO costosMateriales (id, idMaterial, costo, precio, desde) VALUES (:id, :idMaterial, :costo, :precio, :desde);");
        query->bindValue(":id", id());
        query->bindValue(":idMaterial", _idMaterial);
        query->bindValue(":costo", _costo);
        query->bindValue(":precio", _precio);
        query->bindValue(":desde", _desde);
        break;
    }
    case EntityStatus::deleted:
    {
        query = new QSqlQuery(database);
        query->prepare("DELETE FROM costosMateriales WHERE id = :id;");
        query->bindValue(":id", id());
        break;
    }
    case EntityStatus::modified:
    {
        query = new QSqlQuery(database);
        query->prepare("UPDATE costosMateriales SET idMaterial = :idMaterial, costo = :costo, precio = :precio, desde = :desde WHERE id = :id;");
        query->bindValue(":idMaterial", _idMaterial);
        query->bindValue(":costo", _costo);
        query->bindValue(":precio", _precio);
        query->bindValue(":desde", _desde);
        query->bindValue(":id", id());
        break;
    }
    case EntityStatus::unchanged:
        query = NULL;
        break;
    }
    return query;
}

int CostoMaterial::idMaterial() const
{
    return _idMaterial;
}

EntityBasePtr CostoMaterial::material() const
{
    return GlobalContainer::instance().library()->model(Tables::MaterialesYTareas)->getItem(_idMaterial);
}


double CostoMaterial::costo() const
{
    return _costo;
}

double CostoMaterial::precio() const
{
    return _precio;
}

QDate CostoMaterial::desde() const
{
    return _desde;
}

QString CostoMaterial::toDebugString()
{
    return QString("id: %1, idMaterial: %2, costo: %3, precio: %4, desde: %5").arg(id())
            .arg(_idMaterial).arg(costo()).arg(_precio).arg(desde().toString());
}
