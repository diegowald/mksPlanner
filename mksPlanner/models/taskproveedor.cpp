#include "taskproveedor.h"
#include <QVariant>
#include "globalcontainer.h"
#include "models/material.h"


TaskProveedor::TaskProveedor(int id, int idProveedor, int idTask) : EntityBase(id)
{
    _idProveedor = idProveedor;
    _idTask = idTask;
}

TaskProveedor::TaskProveedor(int id) : EntityBase(id, true)
{
    _idProveedor = -1;
    _idTask = -1;
}

bool TaskProveedor::internalSetData(const int column, const QVariant &value, int role)
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
            _idTask = value.toInt();
            break;
        }
        default:
            break;
        }

        return true;
    }
    return false;
}

void TaskProveedor::setIdProveedor(int id)
{
    _idProveedor = id;
    updateStatus(EntityStatus::modified);
}

void TaskProveedor::setIdTask(int id)
{
    _idTask = id;
    updateStatus(EntityStatus::modified);
}

QSqlQuery* TaskProveedor::getQuery(QSqlDatabase &database)
{
    QSqlQuery *query;
    switch (status())
    {
    case EntityStatus::added:
    {
        query = new QSqlQuery(database);
        query->prepare("INSERT INTO tareasProveedores (idProveedor, idTarea) VALUES (:idProveedor, :idTarea);");
        query->bindValue(":idProveedor", _idProveedor);
        query->bindValue(":idTarea", _idTask);
        break;
    }
    case EntityStatus::deleted:
    {
        query = new QSqlQuery(database);
        query->prepare("DELETE FROM tareasProveedores WHERE id = :id;");
        query->bindValue(":id", id());
        break;
    }
    case EntityStatus::modified:
    {
        query = new QSqlQuery(database);
        query->prepare("UPDATE tareasProveedores SET idProveedor = :idProveedor, idTarea = :idTarea WHERE id = :id;");
        query->bindValue(":idProveedor", _idProveedor);
        query->bindValue(":idTarea", _idTask);
        query->bindValue(":id", id());
        break;
    }
    case EntityStatus::unchanged:
        query = NULL;
        break;
    }
    return query;
}

int TaskProveedor::idProveedor() const
{
    return _idProveedor;
}

EntityBasePtr TaskProveedor::proveedor() const
{
    return GlobalContainer::instance().materialLibrary()->model(Tables::Proveedores)->getItem(_idProveedor);
}

int TaskProveedor::idTask() const
{
    return _idTask;
}

EntityBasePtr TaskProveedor::task() const
{
    return GlobalContainer::instance().materialLibrary()->model(Tables::Tareas)->getItem(_idTask);
}

QString TaskProveedor::toDebugString()
{
    return QString("id: %1, idProveedor: %2, idTask: %3")
            .arg(id()).arg(_idProveedor).arg(_idTask);
}
