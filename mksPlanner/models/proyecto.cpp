#include "proyecto.h"
#include <QVariant>
#include "globalcontainer.h"
#include "models/planningtaskmodel.h"
#include "models/planningtask.h"
#include "globalcontainer.h"
#include "models/executiontaskmodel.h"
#include "models/planningtask.h"
#include "models/executiontask.h"
#include "models/executiontaskmodelconstraint.h"

Proyecto::Proyecto(int id, const QString &propietario, const QString &direccion, const QString &email, const QString &telefono,
                   QDate &fechaEstimadaInicio,
                   QDate &fechaEstimadaFinalizacion, ProjectStatus projectStatus)
    : EntityBase(id)
{
    _propietario = propietario;
    _direccion = direccion;
    _email = email;
    _telefono = telefono;
    _fechaEstimadaInicio = fechaEstimadaInicio;
    _fechaEstimadaFinalizacion = fechaEstimadaFinalizacion;
    _status = projectStatus;
}


Proyecto::Proyecto(int id) : EntityBase(id, true)
{
    _propietario = "";
    _direccion = "";
    _email = "";
    _telefono = "";
    _fechaEstimadaInicio = QDate::currentDate();
    _fechaEstimadaFinalizacion = QDate::currentDate().addDays(100);
    _status = ProjectStatus::Planificacion;
}

void Proyecto::setIdProyectoInterno(int value)
{
    _idProyectoInterno = value;
}

QSqlQuery* Proyecto::getQuery(QSqlDatabase &database)
{
    QSqlQuery *query = NULL;
    switch (status())
    {
    case EntityStatus::added:
    {
        query = new QSqlQuery(database);
        query->prepare("INSERT INTO proyectos (id, propietario, direccion, email, telefono, "
                       " fechaEstimadaInicio, fechaEstimadaFinalizacion, status ) "
                       " VALUES (:id, :propietario, :direccion, :email, :telefono, :fechaEstimadaInicio, :fechaEstimadaFinalizacion, :status);");

        query->bindValue(":id", id());
        query->bindValue(":propietario", _propietario);
        query->bindValue(":direccion", _direccion);
        query->bindValue(":email", _email);
        query->bindValue(":telefono", _telefono);
        query->bindValue(":fechaEstimadaInicio", _fechaEstimadaInicio);
        query->bindValue(":fechaEstimadaFinalizacion", _fechaEstimadaFinalizacion);
        query->bindValue(":status", static_cast<int>(_status));
        break;
    }
    case EntityStatus::deleted:
    {
        query = new QSqlQuery(database);
        query->prepare("DELETE FROM proyectos WHERE id = :id;");
        query->bindValue(":id", id());
        break;
    }
    case EntityStatus::modified:
    {
        query = new QSqlQuery(database);
        query->prepare("UPDATE proyectos SET propietario = :propietario, direccion = :direccion, email = :email, telefono = :telefono, "
                       " fechaEstimadaInicio = :fechaEstimadaInicio, "
                       " fechaEstimadaFinalizacion = :fechaEstimadaFinalizacion, status = :status "
                       " WHERE id = :id;");

        query->bindValue(":propietario", _propietario);
        query->bindValue(":direccion", _direccion);
        query->bindValue(":email", _email);
        query->bindValue(":telefono", _telefono);
        query->bindValue(":fechaEstimadaInicio", _fechaEstimadaInicio);
        query->bindValue(":fechaEstimadaFinalizacion", _fechaEstimadaFinalizacion);
        query->bindValue(":status", static_cast<int>(_status));

        query->bindValue(":id", id());
        break;
    }
    case EntityStatus::unchanged:
        query = NULL;
        break;
    }
    return query;
}

QString Proyecto::toDebugString()
{
    return QString("id: %1, propietario: %2, direccion: %3, email: %4, telefono: %5, fechaEstimadaInicio: %6, fechaEstimadaFin: %7")
            .arg(id()).arg(_propietario).arg(_direccion).arg(_email).arg(_telefono)
            .arg(_fechaEstimadaInicio.toString())
            .arg(_fechaEstimadaFinalizacion.toString());

}


QString Proyecto::propietario() const
{
    return _propietario;
}

QString Proyecto::direccion() const
{
    return _direccion;
}

QString Proyecto::email() const
{
    return _email;
}

QString Proyecto::telefono() const
{
    return _telefono;
}

QDate Proyecto::fechaEstimadaInicio() const
{
    return _fechaEstimadaInicio;
}

QDate Proyecto::fechaEstimadaFinalizacion() const
{
    return _fechaEstimadaFinalizacion;
}

void Proyecto::setPropietario(const QString &value)
{
    _propietario = value;
    updateStatus();
}

void Proyecto::setDireccion(const QString &value)
{
    _direccion = value;
    updateStatus();
}

void Proyecto::setEMail(const QString &value)
{
    _email = value;
    updateStatus();
}

void Proyecto::setTelefono(const QString &value)
{
    _telefono = value;
    updateStatus();
}

void Proyecto::setFechaEstimadaInicio(QDate &value)
{
    _fechaEstimadaInicio = value;
    updateStatus();
}

void Proyecto::setFechaEstimadaFinalizacion(QDate &value)
{
    _fechaEstimadaFinalizacion = value;
    updateStatus();
}

int Proyecto::plazoEstimado() const
{
    return _fechaEstimadaFinalizacion.toJulianDay() - _fechaEstimadaInicio.toJulianDay();
}

double Proyecto::costoEstimado() const
{
    double costoAcumulado = 0;
    PlanningTaskModel *ptm = qobject_cast<PlanningTaskModel*>(GlobalContainer::instance().projectLibrary(_idProyectoInterno)->model(Tables::PlanningTasks));
    foreach (EntityBasePtr entity, ptm->tasks())
    {
        PlanningTaskPtr pt = qSharedPointerDynamicCast<PlanningTask>(entity);
        costoAcumulado += pt->costo();
    }
    return costoAcumulado;
}

Proyecto::ProjectStatus Proyecto::projectStatus() const
{
    return _status;
}

QString Proyecto::projectStatusString() const
{
    QString s;
    switch (_status)
    {
    case Proyecto::ProjectStatus::Planificacion:
        s = "Planificación";
        break;
    case Proyecto::ProjectStatus::Ejecucion:
        s = "Ejecución";
        break;
    case Proyecto::ProjectStatus::Finalizado:
        s = "Finalizado";
        break;
    case Proyecto::ProjectStatus::Pausado:
        s = "En pausa";
        break;
    }
    return s;
}

void Proyecto::setProjectStatus(ProjectStatus status)
{
    ProjectStatus statusViejo = _status;
    _status = status;
    if (statusViejo == ProjectStatus::Planificacion && _status == ProjectStatus::Ejecucion)
    {
        crearPlanningEjecucion();
    }
    updateStatus();
}

void Proyecto::crearPlanningEjecucion()
{
    IModel *model = GlobalContainer::instance().projectLibrary(_idProyectoInterno)->model(Tables::ExecutionTasks);
    ExecutionTaskModel *execModel = dynamic_cast<ExecutionTaskModel*>(model);
    execModel->cloneFromPlanning();

    model = GlobalContainer::instance().projectLibrary(_idProyectoInterno)->model(Tables::ExecutionTasksConstraints);
    ExecutionTaskModelConstraint *constraintModel = dynamic_cast<ExecutionTaskModelConstraint*>(model);
    constraintModel->cloneFromPlanning();
}
