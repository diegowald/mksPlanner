#include "planningtask.h"
#include "globalcontainer.h"
#include "models/costomaterial.h"
#include "models/costomaterialesmodel.h"
#include "globalcontainer.h"
#include "models/material.h"
#include "models/cantidad.h"

PlanningTask::PlanningTask(int id) : EntityBase(id, true)
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
}

PlanningTask::PlanningTask(int id, int idTareaPadre, const QString &name,
                      int idMaterialTask, int idProveedor,
                      double cantidad, const QDateTime &fechaEstimadaInicio,
                      const QDateTime &fechaEstimadaFin, KDGantt::ItemType taskType) : EntityBase(id, false)
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

QDateTime PlanningTask::fechaEstimadaInicio() const
{
    return _fechaEstimadaInicio;
}

QDateTime PlanningTask::fechaEstimadaFin() const
{
    return _fechaEstimadaFin;
}

int PlanningTask::duracion() const
{
    return _fechaEstimadaFin.date().toJulianDay() -
            _fechaEstimadaInicio.date().toJulianDay();
}

double PlanningTask::costo() const
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

double PlanningTask::precio() const
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

void PlanningTask::setFechaEstimadaInicio(QDateTime &value)
{
    _fechaEstimadaInicio = value;
    updateStatus();
}

void PlanningTask::setFechaEstimadaFin(QDateTime &value)
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
                       " (id, idTareaPadre, name, idMaterialTask, idProveedor, cantidad, fechaEstimadaInicio, fechaEstimadaFin, taskType) "
                       " VALUES "
                       " (:id, :idTareaPadre, :name, :idMaterialTask, :idProveedor, :cantidad, :fechaEstimadaInicio, :fechaEstimadaFin, :taskType);");

        query->bindValue(":id", id());
        query->bindValue(":idTareaPadre", _idTareaPadre);
        query->bindValue(":name", _name);
        query->bindValue(":idMaterialTask", _idMaterialTask);
        query->bindValue(":idProveedor", _idProveedor);
        query->bindValue(":cantidad", _cantidad);
        query->bindValue(":fechaEstimadaInicio", _fechaEstimadaInicio);
        query->bindValue(":fechaEstimadaFin", _fechaEstimadaFin);
        query->bindValue(":taskType", _taskType);
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
        query->prepare("UPDATE tareasPlanificadas SET idTareaPadre = :idTareaPadre, name = :name, idMaterialTask = :idMaterialTask, idProveedor = :idProveedor, cantidad = :cantidad, fechaEstimadaInicio = :fechaEstimadaInicio, fechaEstimadaFin = :fechaEstimadaFin, taskType = :taskType WHERE id = :id;");

        query->bindValue(":idTareaPadre", _idTareaPadre);
        query->bindValue(":name", _name);
        query->bindValue(":idMaterialTask", _idMaterialTask);
        query->bindValue(":idProveedor", _idProveedor);
        query->bindValue(":cantidad", _cantidad);
        query->bindValue(":fechaEstimadaInicio", _fechaEstimadaInicio);
        query->bindValue(":fechaEstimadaFin", _fechaEstimadaFin);
        query->bindValue(":taskType", _taskType);
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

QString PlanningTask::tooltip() const
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

QString PlanningTask::tablaListadoMateriales() const
{
    QMap<QString, CantidadPtr> listado = listadoMateriales();
    QString result = "";
    QString templ = "<tr><td>%1</td><td>%2</td></tr>";
    foreach (QString material, listado.keys())
    {
        result += templ.arg(material)
                .arg(listado[material]->toString());
    }
    return result;
}

QMap<QString, CantidadPtr> PlanningTask::listadoMateriales() const
{
    QMap<QString, CantidadPtr> result;
    if (_idMaterialTask != -1)
    {
        MaterialPtr material = qSharedPointerDynamicCast<Material>(materialTask());
        QMap<QString, CantidadPtr> processingResult = material->listadoMaterialesCantidades(_cantidad);
        foreach (QString material, processingResult.keys())
        {
            if (!result.contains(material))
                result[material] = processingResult[material];
            else
            {
                CantidadPtr c = result[material];
                c->setValue(c->value() + processingResult[material]->value());
            }
        }
    }
    return result;
}

QList<PlanningTaskPtr> PlanningTask::child() const
{
    return _child;
}

void PlanningTask::addSubTask(PlanningTaskPtr task)
{
    _child.append(task);
}

KDGantt::ItemType PlanningTask::taskType() const
{
    return _taskType;
}

void PlanningTask::setTaskType(KDGantt::ItemType value)
{
    _taskType = value;
    updateStatus();
}

QString PlanningTask::cantidadToString() const
{
    Cantidad c(_cantidad, qSharedPointerDynamicCast<Unit>(qSharedPointerDynamicCast<Material>(materialTask())->unit()));
    return c.toString();
}
