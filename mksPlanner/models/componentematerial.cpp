#include "componentematerial.h"
#include <QVariant>
#include "globalcontainer.h"
#include "models/material.h"
#include "models/unit.h"

ComponenteMaterial::ComponenteMaterial(int id) : EntityBase(id, true)
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
    if (role == Qt::EditRole)
    {
        switch (column)
        {
        case 1:
        {
            _idMaterialPadre = value.toInt();
            break;
        }
        case 2:
        {
            _idMaterial = value.toInt();
            break;
        }
        case 4:
        {
            _cantidad = value.toDouble();
            break;
        }
        default:
            break;
        }

        return true;
    }
    return false;
}

void ComponenteMaterial::setIdMaterialPadre(int id)
{
    _idMaterialPadre = id;
    updateStatus(EntityStatus::modified);
}

void ComponenteMaterial::setIdMaterial(int id)
{
    _idMaterial = id;
    updateStatus(EntityStatus::modified);
}

void ComponenteMaterial::setCantidad(double value)
{
    _cantidad = value;
    updateStatus(EntityStatus::modified);
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


int ComponenteMaterial::idMaterialPadre() const
{
    return _idMaterialPadre;
}

EntityBasePtr ComponenteMaterial::materialPadre() const
{
    return GlobalContainer::instance().library()->model(Tables::Materiales)->getItem(_idMaterialPadre);
}

int ComponenteMaterial::idMaterial() const
{
    return _idMaterial;
}

EntityBasePtr ComponenteMaterial::material() const
{
    return GlobalContainer::instance().library()->model(Tables::Materiales)->getItem(_idMaterial);
}

double ComponenteMaterial::cantidad() const
{
    return _cantidad;
}

QString ComponenteMaterial::toDebugString()
{
    return QString("id: %1, idMaterialPadre: %2, idMaterial: %3, cantidad: %4").arg(id())
            .arg(_idMaterialPadre).arg(_idMaterial).arg(_cantidad);
}
