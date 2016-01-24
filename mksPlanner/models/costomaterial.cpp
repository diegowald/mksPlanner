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

CostoMaterial::CostoMaterial(int id, int idMaterial, double costo, QDate desde) : EntityBase(id)
{
    _idMaterial = idMaterial;
    _costo = costo;
    _desde = desde;
}


bool CostoMaterial::internalSetData(const int column, const QVariant &value, int role)
{
    if (role == Qt::EditRole)
    {
        switch (column)
        {
        case 1:
        {
            _idMaterial = value.toInt();
            break;
        }
        case 2:
        {
            _costo = value.toDouble();
            break;
        }
        case 3:
        {
            _desde = value.toDate();
            break;
        }
        default:
            break;
        }

        return true;
    }
    return false;
}

void CostoMaterial::setIdMaterial(int id)
{
    _idMaterial = id;
    updateStatus(EntityStatus::modified);
}

void CostoMaterial::setCosto(double value)
{
    _costo = value;
    updateStatus(EntityStatus::modified);
}

void CostoMaterial::setDesde(QDate &date)
{
    _desde = date;
    updateStatus(EntityStatus::modified);
}

/*QVariant CostoMaterial::internalData(const int column, int role) const
{
    QVariant result;
    if (role == Qt::DisplayRole)
    {
        switch (column)
        {
        case 0:
        {
            result = id();
            break;
        }
        case 1:
        {
            result = _idMaterial;
            break;
        }
        case 2:
        {
            result = _costo;
            break;
        }
        case 3:
        {
            result = _desde;
            break;
        }
        default:
            break;
        }
    }
    return result;
}*/

QSqlQuery* CostoMaterial::getQuery(QSqlDatabase &database)
{
    QSqlQuery *query;
    switch (status())
    {
    case EntityStatus::added:
    {
        query = new QSqlQuery(database);
        query->prepare("INSERT INTO costosMateriales (idMaterial, costo, desde) VALUES (:idMaterial, :costo, :desde);");
        query->bindValue(":idMaterial", _idMaterial);
        query->bindValue(":costo", _costo);
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
        query->prepare("UPDATE costosMateriales SET idMaterial = :idMaterial, costo = :costo, desde = :desde WHERE id = :id;");
        query->bindValue(":idMaterial", _idMaterial);
        query->bindValue(":costo", _costo);
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
    return GlobalContainer::instance().materialLibrary()->model(Tables::Materiales)->getItem(_idMaterial);
}


double CostoMaterial::costo() const
{
    return _costo;
}

QDate CostoMaterial::desde() const
{
    return _desde;
}

QString CostoMaterial::toDebugString()
{
    return QString("id: %1, idMaterial: %2, costo: %3, desde: %4").arg(id())
            .arg(_idMaterial).arg(costo()).arg(desde().toString());
}
