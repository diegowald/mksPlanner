#include "rubroroveedor.h"
#include <QVariant>
#include "globalcontainer.h"
#include "models/material.h"


RubroProveedor::RubroProveedor(int id, int idProveedor, int idRubro) : EntityBase(id)
{
    _idProveedor = idProveedor;
    _idRubro = idRubro;
}

RubroProveedor::RubroProveedor(int id) : EntityBase(id, true)
{
    _idProveedor = -1;
    _idRubro = -1;
}

bool RubroProveedor::internalSetData(const int column, const QVariant &value, int role)
{
    if (role == Qt::EditRole)
    {
        switch (column)
        {
        case 1:
        {
            _idProveedor = value.toInt();
            break;
        }
        case 2:
        {
            _idRubro = value.toInt();
            break;
        }
        default:
            break;
        }

        return true;
    }
    return false;
}

void RubroProveedor::setIdProveedor(int id)
{
    _idProveedor = id;
    updateStatus(EntityStatus::modified);
}

void RubroProveedor::setIdRubro(int id)
{
    _idRubro = id;
    updateStatus(EntityStatus::modified);
}

QSqlQuery* RubroProveedor::getQuery(QSqlDatabase &database)
{
    QSqlQuery *query;
    switch (status())
    {
    case EntityStatus::added:
    {
        query = new QSqlQuery(database);
        query->prepare("INSERT INTO rubrosProveedores (idProveedor, idRubro) VALUES (:idProveedor, :idRubro);");
        query->bindValue(":idProveedor", _idProveedor);
        query->bindValue(":idRubro", _idRubro);
        break;
    }
    case EntityStatus::deleted:
    {
        query = new QSqlQuery(database);
        query->prepare("DELETE FROM rubrosProveedores WHERE id = :id;");
        query->bindValue(":id", id());
        break;
    }
    case EntityStatus::modified:
    {
        query = new QSqlQuery(database);
        query->prepare("UPDATE rubrosProveedores SET idProveedor = :idProveedor, idRubro = :idrubro WHERE id = :id;");
        query->bindValue(":idProveedor", _idProveedor);
        query->bindValue(":idrubro", _idRubro);
        query->bindValue(":id", id());
        break;
    }
    case EntityStatus::unchanged:
        query = NULL;
        break;
    }
    return query;
}

int RubroProveedor::idProveedor() const
{
    return _idProveedor;
}

EntityBasePtr RubroProveedor::proveedor() const
{
    return GlobalContainer::instance().library()->model(Tables::Proveedores)->getItem(_idProveedor);
}

int RubroProveedor::idRubro() const
{
    return _idRubro;
}

EntityBasePtr RubroProveedor::rubro() const
{
    return GlobalContainer::instance().library()->model(Tables::Rubros)->getItem(_idRubro);
}

QString RubroProveedor::toDebugString()
{
    return QString("id: %1, idProveedor: %2, idrubro: %3")
            .arg(id()).arg(_idProveedor).arg(_idRubro);
}
