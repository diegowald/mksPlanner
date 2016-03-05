#include "executiontask.h"
#include "globalcontainer.h"
#include "models/costomaterial.h"
#include "models/costomaterialesmodel.h"
#include "globalcontainer.h"
#include "models/material.h"
#include "models/planningtask.h"

ExecutionTask::ExecutionTask(int id) : EntityBase(id, true)
{
    _idProyecto = -1;
    _idTareaPadre = -1;
    _name = "";
    _idMaterialTask = -1;
    _idProveedor = -1;
    _cantidad = 0.;
    _fechaEstimadaInicio = QDateTime::currentDateTime();
    _fechaEstimadaInicio.setTime(QTime(0, 0, 0));
    _fechaEstimadaFin = QDateTime::currentDateTime().addDays(1);
    _fechaEstimadaFin.setTime(QTime(23, 59, 59, 999));
    _taskType = KDGantt::TypeTask;
    _idPlanningTask = -1;
    _pctCompletado = 0.;
    _fechaRealInicio = QDateTime::currentDateTime();
    _fechaRealInicio.setTime(QTime(0, 0, 0));
    _fechaRealFin = QDateTime::currentDateTime().addDays(1);
    _fechaRealFin.setTime(QTime(23, 59, 59, 999));
}

ExecutionTask::ExecutionTask(int id, int idTareaPadre, const QString &name,
                      int idMaterialTask, int idProveedor,
                      double cantidad, const QDateTime &fechaEstimadaInicio,
                      const QDateTime &fechaEstimadaFin, KDGantt::ItemType taskType, int idTareaPlanificada, double pctCompletado, const QDateTime &fechaRealInicio, const QDateTime &fechaRealFin) : EntityBase(id, false)
{
    _idProyecto = -1;
    _idTareaPadre = idTareaPadre;
    _name = name;
    _idMaterialTask = idMaterialTask;
    _idProveedor = idProveedor;
    _cantidad = cantidad;
    _fechaEstimadaInicio = fechaEstimadaInicio;
    _fechaEstimadaFin = fechaEstimadaFin;
    _taskType = taskType;
    _idPlanningTask = idTareaPlanificada;
    _pctCompletado = pctCompletado;
    _fechaRealInicio = fechaRealInicio;
    _fechaRealFin = fechaRealFin;
}

int ExecutionTask::idPlanningTask() const
{
    return _idPlanningTask;
}

EntityBasePtr ExecutionTask::planningTask() const
{
    return GlobalContainer::instance().projectLibrary(_idProyecto)->model(Tables::PlanningTasks)->getItem(_idPlanningTask);
}

int ExecutionTask::idTareaPadre() const
{
    return _idTareaPadre;
}

EntityBasePtr ExecutionTask::tareaPadre() const
{
    return GlobalContainer::instance().projectLibrary(_idProyecto)->model(Tables::PlanningTasks)->getItem(_idTareaPadre);
}

QString ExecutionTask::name() const
{
    return _name;
}


int ExecutionTask::idMaterialTask() const
{
    return _idMaterialTask;
}

EntityBasePtr ExecutionTask::materialTask() const
{
    return GlobalContainer::instance().library()->model(Tables::Materiales)->getItem(_idMaterialTask);
}

int ExecutionTask::idProveedor() const
{
    return _idProveedor;
}

EntityBasePtr ExecutionTask::proveedor() const
{
    return GlobalContainer::instance().library()->model(Tables::Proveedores)->getItem(_idProveedor);
}

double ExecutionTask::cantidad() const
{
    return _cantidad;
}

QDateTime ExecutionTask::fechaEstimadaInicio() const
{
    return _fechaEstimadaInicio;
}

QDateTime ExecutionTask::fechaEstimadaFin() const
{
    return _fechaEstimadaFin;
}

int ExecutionTask::duracion() const
{
    return _fechaEstimadaFin.date().toJulianDay() -
            _fechaEstimadaInicio.date().toJulianDay();
}

double ExecutionTask::costo() const
{
    if (_idMaterialTask != -1)
    {
        CostoMaterialesModel *model = qobject_cast<CostoMaterialesModel*>(GlobalContainer::instance().library()->model(Tables::CostosUnitarios));
        CostoMaterialPtr costo = qSharedPointerDynamicCast<CostoMaterial>(model->getItemByIdMaterial(_idMaterialTask));
        if (!costo.isNull())
            return _cantidad * costo->costo();
    }
    return -1;
}

double ExecutionTask::precio() const
{
    if (_idMaterialTask != -1)
    {
        CostoMaterialesModel *model = qobject_cast<CostoMaterialesModel*>(GlobalContainer::instance().library()->model(Tables::CostosUnitarios));
        CostoMaterialPtr costo = qSharedPointerDynamicCast<CostoMaterial>(model->getItemByIdMaterial(_idMaterialTask));
        if (!costo.isNull())
            return _cantidad * costo->precio();
    }
    return -1;
}

void ExecutionTask::setIdTareaPadre(int value)
{
    _idTareaPadre = value;
    updateStatus();
}

void ExecutionTask::setName(const QString &value)
{
    _name = value;
    updateStatus();
}

void ExecutionTask::setIdMaterialTask(int value)
{
    _idMaterialTask = value;
    updateStatus();
}

void ExecutionTask::setIdProveedor(int value)
{
    _idProveedor = value;
    updateStatus();
}

void ExecutionTask::setCantidad(double value)
{
    _cantidad = value;
    updateStatus();
}

void ExecutionTask::setFechaEstimadaInicio(QDateTime &value)
{
    _fechaEstimadaInicio = value;
    updateStatus();
}

void ExecutionTask::setFechaEstimadaFin(QDateTime &value)
{
    _fechaEstimadaFin = value;
    updateStatus();
}



QString ExecutionTask::toDebugString()
{
    return QString("id: %1, idTareaPadre: %2, name: %3, idMaterialTask: %4, idProveedor: %5, "
                   "cantidad: %6, fechaEstimadaInicio: %7, fechaEstimadaFin: %8)")
            .arg(_idTareaPadre).arg(_name).arg(_idMaterialTask)
            .arg(_idProveedor).arg(_cantidad).arg(_fechaEstimadaInicio.toString())
            .arg(_fechaEstimadaFin.toString());
}

QSqlQuery *ExecutionTask::getQuery(QSqlDatabase &database)
{
    QSqlQuery *query;
    switch (status())
    {
    case EntityStatus::added:
    {
        query = new QSqlQuery(database);
        query->prepare("INSERT INTO tareasEjecucion "
                       " (id, idTareaPadre, name, idMaterialTask, idProveedor, cantidad, fechaEstimadaInicio, fechaEstimadaFin, taskType, idTareaPlanificada, pctAvance, fechaRealInicio, fechaRealFin) "
                       " VALUES "
                       " (:id, :idTareaPadre, :name, :idMaterialTask, :idProveedor, :cantidad, :fechaEstimadaInicio, :fechaEstimadaFin, :taskType, :idTareaPlanificada, :pctAvance, :fechaRealInicio, :fechaRealFin);");

        query->bindValue(":id", id());
        query->bindValue(":idTareaPadre", _idTareaPadre);
        query->bindValue(":name", _name);
        query->bindValue(":idMaterialTask", _idMaterialTask);
        query->bindValue(":idProveedor", _idProveedor);
        query->bindValue(":cantidad", _cantidad);
        query->bindValue(":fechaEstimadaInicio", _fechaEstimadaInicio);
        query->bindValue(":fechaEstimadaFin", _fechaEstimadaFin);
        query->bindValue(":taskType", _taskType);
        query->bindValue(":idTareaPlanificada", _idPlanningTask);
        query->bindValue(":pctAvance", _pctCompletado);
        query->bindValue(":fechaRealInicio", _fechaRealInicio);
        query->bindValue(":fechaRealFin", _fechaRealFin);

        break;
    }
    case EntityStatus::deleted:
    {
        query = new QSqlQuery(database);
        query->prepare("DELETE FROM tareasEjecucion WHERE id = :id;");
        query->bindValue(":id", id());
        break;
    }
    case EntityStatus::modified:
    {
        query = new QSqlQuery(database);
        query->prepare("UPDATE tareasEjecucion SET idTareaPadre = :idTareaPadre, name = :name, idMaterialTask = :idMaterialTask, idProveedor = :idProveedor, cantidad = :cantidad, fechaEstimadaInicio = :fechaEstimadaInicio, fechaEstimadaFin = :fechaEstimadaFin, taskType = :taskType, idTareaPlanificada = :idTareaPlanificada, pctAvance = :pctAvance, fechaRealInicio = :fechaRealInicio, fechaRealFin = :fechaRealFin WHERE id = :id;");

        query->bindValue(":idTareaPadre", _idTareaPadre);
        query->bindValue(":name", _name);
        query->bindValue(":idMaterialTask", _idMaterialTask);
        query->bindValue(":idProveedor", _idProveedor);
        query->bindValue(":cantidad", _cantidad);
        query->bindValue(":fechaEstimadaInicio", _fechaEstimadaInicio);
        query->bindValue(":fechaEstimadaFin", _fechaEstimadaFin);
        query->bindValue(":taskType", _taskType);
        query->bindValue(":idTareaPlanificada", _idPlanningTask);
        query->bindValue(":pctAvance", _pctCompletado);
        query->bindValue(":fechaRealInicio", _fechaRealInicio);
        query->bindValue(":fechaRealFin", _fechaRealFin);

        query->bindValue(":id", id());
        break;
    }
    case EntityStatus::unchanged:
        query = NULL;
        break;
    }
    return query;
}


void ExecutionTask::setIdProyecto(int idProyecto)
{
    _idProyecto = idProyecto;
}

QString ExecutionTask::tooltip() const
{
    QString s = "<table>"
                "<tr>"
                "<td colspan=\"2\">%1</td></tr>"
                "<td colspan=\"2\">%2</td>"
                "</tr>%3</table>";
    return s.arg(_name)
            .arg(tr("Materiales"))
            .arg(tablaListadoMateriales());
}

QString ExecutionTask::tablaListadoMateriales() const
{
    QMap<QString, double> listado = listadoMateriales();
    QString result = "";
    QString templ = "<tr><td>%1</td><td>%2 %3</td></tr>";
    foreach (QString material, listado.keys())
    {
        result += templ.arg(material)
                .arg(listado[material]);
    }
    return result;
}

QMap<QString, double> ExecutionTask::listadoMateriales() const
{
    QMap<QString, double> result;
    if (_idMaterialTask != -1)
    {
        MaterialPtr material = qSharedPointerDynamicCast<Material>(materialTask());
        QMap<QString, double> processingResult = material->listadoMaterialesCantidades(_cantidad);
        foreach (QString material, processingResult.keys())
        {
            if (!result.contains(material))
                result[material] = processingResult[material];
            else
                result[material] += processingResult[material];
        }
    }
    return result;
}

QList<ExecutionTaskPtr> ExecutionTask::child() const
{
    return _child;
}

void ExecutionTask::addSubTask(ExecutionTaskPtr task)
{
    _child.append(task);
}

KDGantt::ItemType ExecutionTask::taskType() const
{
    return _taskType;
}

void ExecutionTask::setTaskType(KDGantt::ItemType value)
{
    _taskType = value;
    updateStatus();
}

void ExecutionTask::setPlanningTask(EntityBasePtr entity, bool copyData)
{
    setIdPlanningTask(entity->id());
    if (copyData)
    {
        PlanningTaskPtr pt = qSharedPointerDynamicCast<PlanningTask>(entity);

        setIdTareaPadre(pt->idTareaPadre()); // esto hay que hacerlo bien
        setName(pt->name());
        setIdMaterialTask(pt->idMaterialTask());
        setIdProveedor(pt->idProveedor());
        setCantidad(pt->cantidad());
        QDateTime dt = pt->fechaEstimadaInicio();
        setFechaEstimadaInicio(dt);
        dt = pt->fechaEstimadaFin();
        setFechaEstimadaFin(dt);
        setTaskType(pt->taskType());
    }
}

void ExecutionTask::setIdPlanningTask(int value)
{
    _idPlanningTask = value;
    updateStatus();
}

double ExecutionTask::pctCompletado() const
{
    return _pctCompletado;
}

void ExecutionTask::setPctCompletado(double value)
{
    _pctCompletado = value;
    updateStatus();
}
