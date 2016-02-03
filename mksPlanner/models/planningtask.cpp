#include "planningtask.h"
#include "globalcontainer.h"


PlanningTask::PlanningTask(int id) : EntityBase(id, true)
{
    _idProyecto = -1;
}

PlanningTask::PlanningTask(int id, int idTareaPadre, const QString &name,
                      int idMaterialTask, int idProveedor,
                      double cantidad, const QDate &fechaEstimadaInicio,
                      const QDate &fechaEstimadaFin) : EntityBase(id, false)
{
    _idProyecto = -1;
    _idTareaPadre = idTareaPadre;
    _name = name;
    _idMaterialTask = idMaterialTask;
    _idProveedor = idProveedor;
    _cantidad = cantidad;
    _fechaEstimadaInicio = fechaEstimadaInicio;
    _fechaEstimadaFin = fechaEstimadaFin;
}

int PlanningTask::idTareaPadre() const
{
    return _idTareaPadre;
}

EntityBasePtr PlanningTask::tareaPadre() const
{
    return GlobalContainer::instance().projectLibrary(_idProyecto)->model(Tables::PlanningTasks)->getItem(_idTareaPadre);
}

QString PlanningTask::name() const
{
    return _name;
}


int PlanningTask::idMaterialTask() const
{
    return _idMaterialTask;
}

EntityBasePtr PlanningTask::materialTask() const
{
    return GlobalContainer::instance().library()->model(Tables::Materiales)->getItem(_idMaterialTask);
}

int PlanningTask::idProveedor() const
{
    return _idProveedor;
}

EntityBasePtr PlanningTask::proveedor() const
{
    return GlobalContainer::instance().library()->model(Tables::Proveedores)->getItem(_idProveedor);
}

double PlanningTask::cantidad() const
{
    return _cantidad;
}

QDate PlanningTask::fechaEstimadaInicio() const
{
    return _fechaEstimadaInicio;
}

QDate PlanningTask::fechaEstimadaFin() const
{
    return _fechaEstimadaFin;
}

int PlanningTask::duracion() const
{
    return _fechaEstimadaFin.toJulianDay() - _fechaEstimadaInicio.toJulianDay();
}

double PlanningTask::costo() const
{
    return -1;
}

double PlanningTask::precio() const
{
    return -1;
}

void PlanningTask::setIdTareaPadre(int value)
{
    _idTareaPadre = value;
    updateStatus();
}

void PlanningTask::setName(const QString &value)
{
    _name = value;
    updateStatus();
}

void PlanningTask::setIdMaterialTask(int value)
{
    _idMaterialTask = value;
    updateStatus();
}

void PlanningTask::setIdProveedor(int value)
{
    _idProveedor = value;
    updateStatus();
}

void PlanningTask::setCantidad(double value)
{
    _cantidad = value;
    updateStatus();
}

void PlanningTask::setFechaEstimadaInicio(QDate &value)
{
    _fechaEstimadaInicio = value;
    updateStatus();
}

void PlanningTask::setFechaEstimadaFin(QDate &value)
{
    _fechaEstimadaFin = value;
    updateStatus();
}



QString PlanningTask::toDebugString()
{
    return QString("id: %1, idTareaPadre: %2, name: %3, idMaterialTask: %4, idProveedor: %5, "
                   "cantidad: %6, fechaEstimadaInicio: %7, fechaEstimadaFin: %8)")
            .arg(_idTareaPadre).arg(_name).arg(_idMaterialTask)
            .arg(_idProveedor).arg(_cantidad).arg(_fechaEstimadaInicio.toString())
            .arg(_fechaEstimadaFin.toString());
}

QSqlQuery *PlanningTask::getQuery(QSqlDatabase &database)
{
    QSqlQuery *query;
    switch (status())
    {
    case EntityStatus::added:
    {
        query = new QSqlQuery(database);
        query->prepare("INSERT INTO tareasPlanificadas "
                       " (idTareaPadre, name, idMaterialTask, idProveedor, cantidad, fechaEstimadaInicio, fechaEstimadaFin) "
                       " VALUES "
                       " (:idTareaPadre, :name, :idMaterialTask, :idProveedor, :cantidad, :fechaEstimadaInicio, :fechaEstimadaFin);");

        query->bindValue(":idTareaPadre", _idTareaPadre);
        query->bindValue(":name", _name);
        query->bindValue(":idMaterialTask", _idMaterialTask);
        query->bindValue(":idProveedor", _idProveedor);
        query->bindValue(":cantidad", _cantidad);
        query->bindValue(":fechaEstimadaInicio", _fechaEstimadaInicio);
        query->bindValue(":fechaEstimadaFin", _fechaEstimadaFin);

        break;
    }
    case EntityStatus::deleted:
    {
        query = new QSqlQuery(database);
        query->prepare("DELETE FROM tareasPlanificadas WHERE id = :id;");
        query->bindValue(":id", id());
        break;
    }
    case EntityStatus::modified:
    {
        query = new QSqlQuery(database);
        query->prepare("UPDATE tareasPlanificadas SET idTareaPadre = :idTareaPadre, name = :name, idMaterialTask = :idMaterialTask, idProveedor = :idProveedor, cantidad = :cantidad, fechaEstimadaInicio = :fechaEstimadaInicio, fechaEstimadaFin = :fechaEstimadaFin WHERE id = :id;");

        query->bindValue(":idTareaPadre", _idTareaPadre);
        query->bindValue(":name", _name);
        query->bindValue(":idMaterialTask", _idMaterialTask);
        query->bindValue(":idProveedor", _idProveedor);
        query->bindValue(":cantidad", _cantidad);
        query->bindValue(":fechaEstimadaInicio", _fechaEstimadaInicio);
        query->bindValue(":fechaEstimadaFin", _fechaEstimadaFin);
        query->bindValue(":id", id());
        break;
    }
    case EntityStatus::unchanged:
        query = NULL;
        break;
    }
    return query;
}


void PlanningTask::setIdProyecto(int idProyecto)
{
    _idProyecto = idProyecto;
}
