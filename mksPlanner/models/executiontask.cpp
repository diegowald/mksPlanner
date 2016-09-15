#include "executiontask.h"
#include "globalcontainer.h"
#include "models/costomaterial.h"
#include "models/costomaterialesmodel.h"
#include "globalcontainer.h"
#include "models/material.h"
#include "models/planningtask.h"
#include "models/executiontaskmodel.h"
#include "models/cantidad.h"
#include "models/certificacionesmodel.h"

ExecutionTask::ExecutionTask(int id) : EntityBase(id, true)
{
    _idProyecto = -1;
    _idTareaPadre = -1;
    _name = "";
    _idMaterialTask = -1;
    _idProveedor = -1;
    _cantidad = 0.;
    _cantidadRealizada = 0.;
    _fechaEstimadaInicio = QDateTime::currentDateTime();
    _fechaEstimadaInicio.setTime(QTime(0, 0, 0));
    _fechaEstimadaFin = QDateTime::currentDateTime().addDays(1);
    _fechaEstimadaFin.setTime(QTime(23, 59, 59, 999));
    _taskType = KDGantt::TypeTask;
    _idPlanningTask = -1;
    //_pctCompletado = 0.;
    _fechaRealInicio = QDateTime::currentDateTime();
    _fechaRealInicio.setTime(QTime(0, 0, 0));
    _fechaRealFin = QDateTime::currentDateTime().addDays(1);
    _fechaRealFin.setTime(QTime(23, 59, 59, 999));
    _isSplittedPart = false;
    _idCertificacion = -1;
}

ExecutionTask::ExecutionTask(int id, int idTareaPadre, const QString &name,
                             int idMaterialTask, int idProveedor,
                             double cantidad, const QDateTime &fechaEstimadaInicio,
                             const QDateTime &fechaEstimadaFin, KDGantt::ItemType taskType,
                             int idTareaPlanificada, const QDateTime &fechaRealInicio,
                             const QDateTime &fechaRealFin, bool isSplittedPart, int idCertificacion,
                             double cantidadRealizada) : EntityBase(id, false)
{
    _idProyecto = -1;
    _idTareaPadre = idTareaPadre;
    _name = name;
    _idMaterialTask = idMaterialTask;
    _idProveedor = idProveedor;
    _cantidad = cantidad;
    _cantidadRealizada = cantidadRealizada;
    _fechaEstimadaInicio = fechaEstimadaInicio;
    _fechaEstimadaFin = fechaEstimadaFin;
    _taskType = taskType;
    _idPlanningTask = idTareaPlanificada;
    //_pctCompletado = pctCompletado;
    _fechaRealInicio = fechaRealInicio;
    _fechaRealFin = fechaRealFin;
    _isSplittedPart = isSplittedPart;
    _idCertificacion = idCertificacion;
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
    return GlobalContainer::instance().projectLibrary(_idProyecto)->model(Tables::ExecutionTasks)->getItem(_idTareaPadre);
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
    return GlobalContainer::instance().library()->model(Tables::Tareas)->getItem(_idMaterialTask);
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
    if (_isSplittedPart)
    {
        EntityBasePtr e = GlobalContainer::instance().projectLibrary(_idProyecto)->model(Tables::ExecutionTasks)->getItem(_idTareaPadre);
        ExecutionTaskPtr et = qSharedPointerDynamicCast<ExecutionTask>(e);
        return et->cantidad();
    }
    else
    {
        return _cantidad;
    }
}

double ExecutionTask::cantidadRealizada() const
{
    if (_isSplittedPart || (child().count() == 0))
    {
        return _cantidadRealizada;
    }
    else
    {
        double cantR = 0.;
        foreach (ExecutionTaskPtr et, child())
        {
            cantR += et->cantidadRealizada();
        }
        return cantR;
    }
}

double ExecutionTask::cantidadCertificada() const
{
    double cantCertificada = 0.;
    if (!_isSplittedPart)
    {
        foreach (ExecutionTaskPtr et, child())
        {
            cantCertificada += et->cantidadCertificada();
        }
    }
    else
    {
        // es una parte splitted
        CertificacionesModel *m = dynamic_cast<CertificacionesModel*>(GlobalContainer::instance().projectLibrary(_idProyecto)->model(Tables::Certificaciones));
        if (_idCertificacion != -1)
        {
            CertificacionPtr cert = m->cast(m->getItem(_idCertificacion));
            cantCertificada += (cert->certificacionStatus() == Certificacion::CertificacionStatus::Emitido) ? _cantidadRealizada : 0;
        }
    }

    return cantCertificada;
}

QDateTime ExecutionTask::fechaEstimadaInicio() const
{
    return _fechaEstimadaInicio;
}

QDateTime ExecutionTask::fechaEstimadaFin() const
{
    return _fechaEstimadaFin;
}

QDateTime ExecutionTask::fechaRealInicio() const
{
    return _fechaRealInicio;
}

QDateTime ExecutionTask::fechaRealFin() const
{
    return _fechaRealFin;
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

double ExecutionTask::costoAcumulado() const
{
    if (_idMaterialTask != -1)
    {
        CostoMaterialesModel *model = qobject_cast<CostoMaterialesModel*>(GlobalContainer::instance().library()->model(Tables::CostosUnitarios));
        CostoMaterialPtr costo = qSharedPointerDynamicCast<CostoMaterial>(model->getItemByIdMaterial(_idMaterialTask));
        if (!costo.isNull())
        {
            return this->cantidadCertificada() * costo->costo();
        }
    }
    return -1;
}

double ExecutionTask::precioAcumulado() const
{
    if (_idMaterialTask != -1)
    {
        CostoMaterialesModel *model = qobject_cast<CostoMaterialesModel*>(GlobalContainer::instance().library()->model(Tables::CostosUnitarios));
        CostoMaterialPtr costo = qSharedPointerDynamicCast<CostoMaterial>(model->getItemByIdMaterial(_idMaterialTask));
        if (!costo.isNull())
        {
            return this->cantidadCertificada() * costo->precio();
        }
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

void ExecutionTask::setCantidadRealizadaEnSubTarea(double value)
{
    _cantidadRealizada = value;
    updateStatus();
}

void ExecutionTask::setFechaEstimadaInicio(const QDateTime &value)
{
    _fechaEstimadaInicio = value;
    updateStatus();
}

void ExecutionTask::setFechaEstimadaFin(const QDateTime &value)
{
    _fechaEstimadaFin = value;
    updateStatus();
}

void ExecutionTask::setFechaRealInicio(const QDateTime &value)
{
    _fechaRealInicio = value;
    updateStatus();
}

void ExecutionTask::setFechaRealFin(const QDateTime &value)
{
    _fechaRealFin = value;
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
    QSqlQuery *query = NULL;
    switch (status())
    {
    case EntityStatus::added:
    {
        query = new QSqlQuery(database);
        query->prepare("INSERT INTO tareasEjecucion "
                       " (id, idTareaPadre, name, idMaterialTask, idProveedor, cantidad, fechaEstimadaInicio, fechaEstimadaFin, taskType, idTareaPlanificada, pctAvance, fechaRealInicio, fechaRealFin, isSplittedPart, idCertificacion, cantidadRealiada) "
                       " VALUES "
                       " (:id, :idTareaPadre, :name, :idMaterialTask, :idProveedor, :cantidad, :fechaEstimadaInicio, :fechaEstimadaFin, :taskType, :idTareaPlanificada, :pctAvance, :fechaRealInicio, :fechaRealFin, :isSplittedPart, :idCertificacion, :cantidadRealiada);");

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
        query->bindValue(":pctAvance", 0/*_pctCompletado*/);
        query->bindValue(":fechaRealInicio", _fechaRealInicio);
        query->bindValue(":fechaRealFin", _fechaRealFin);
        query->bindValue(":isSplittedPart", _isSplittedPart);
        query->bindValue(":idCertificacion", _idCertificacion);
        query->bindValue(":cantidadRealizada", _cantidadRealizada);

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
        query->prepare("UPDATE tareasEjecucion SET idTareaPadre = :idTareaPadre, name = :name, idMaterialTask = :idMaterialTask, idProveedor = :idProveedor, cantidad = :cantidad, fechaEstimadaInicio = :fechaEstimadaInicio, fechaEstimadaFin = :fechaEstimadaFin, taskType = :taskType, idTareaPlanificada = :idTareaPlanificada, pctAvance = :pctAvance, fechaRealInicio = :fechaRealInicio, fechaRealFin = :fechaRealFin, isSplittedPart = :isSplittedPart, idCertificacion = :idCertificacion, cantidadRealizada = :cantidadRealizada WHERE id = :id;");

        query->bindValue(":idTareaPadre", _idTareaPadre);
        query->bindValue(":name", _name);
        query->bindValue(":idMaterialTask", _idMaterialTask);
        query->bindValue(":idProveedor", _idProveedor);
        query->bindValue(":cantidad", _cantidad);
        query->bindValue(":fechaEstimadaInicio", _fechaEstimadaInicio);
        query->bindValue(":fechaEstimadaFin", _fechaEstimadaFin);
        query->bindValue(":taskType", _taskType);
        query->bindValue(":idTareaPlanificada", _idPlanningTask);
        query->bindValue(":pctAvance", 0/*_pctCompletado*/);
        query->bindValue(":fechaRealInicio", _fechaRealInicio);
        query->bindValue(":fechaRealFin", _fechaRealFin);
        query->bindValue(":isSplittedPart", _isSplittedPart);
        query->bindValue(":idCertificacion", _idCertificacion);
        query->bindValue(":cantidadRealizada", _cantidadRealizada);

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

QMap<QString, CantidadPtr> ExecutionTask::listadoMateriales() const
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

QList<ExecutionTaskPtr> ExecutionTask::child() const
{
    IModel *m = GlobalContainer::instance().projectLibrary(_idProyecto)->model(Tables::ExecutionTasks);
    ExecutionTaskModel *etm= static_cast<ExecutionTaskModel*>(m);
    QSet<int> childIds = etm->childIds(id());
    QList<ExecutionTaskPtr> result;
    foreach (int id, childIds.values())
    {
        result.append(etm->cast(etm->getItem(id)));
    }
    return result;
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

        //ExecutionTaskModel *m = qobject_cast<ExecutionTaskModel*>(GlobalContainer::instance().projectLibrary(_idProyecto)->model(Tables::ExecutionTasks));
        //setIdTareaPadre(m->idFromPlanning(pt->idTareaPadre()));
        setName(pt->name());
        setIdMaterialTask(pt->idMaterialTask());
        setIdProveedor(pt->idProveedor());
        setCantidad(pt->cantidad());
        QDateTime dt = pt->fechaEstimadaInicio();
        setFechaRealInicio(dt);
        setFechaEstimadaInicio(dt);
        dt = pt->fechaEstimadaFin();
        setFechaEstimadaFin(dt);
        setFechaRealFin(dt);
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
    return cantidadRealizada() / cantidad() * 100.;
}

double ExecutionTask::pctCompletadoInSubTask() const
{
    if (_isSplittedPart)
    {
        return _cantidadRealizada / _cantidad * 100.;
    }
    return 0.;
}

void ExecutionTask::markAsCompleted()
{
    _cantidad = _cantidadRealizada;
}

void ExecutionTask::setPctCompletado(double value)
{
    if (value != pctCompletado())
    {
        if (!_isSplittedPart)
        {
            double realizadoNuevo = value / 100. * cantidad();
            double hecho = cantidadRealizada() - cantidadCertificada();
            double hechoEnEstaTarea = realizadoNuevo - hecho;
            int idCertificacionNueva = -1;
            if (hechoEnEstaTarea != _cantidadRealizada)
            {
                if (_cantidadRealizada == 0.)
                {
                    CertificacionesModel *m = static_cast<CertificacionesModel*>(GlobalContainer::instance().projectLibrary(_idProyecto)->model(Tables::Certificaciones));
                    idCertificacionNueva = m->idCertificacionProxima(fechaRealInicio().date(), true);
                }
            }

            if (child().count() == 0)
            {
                _cantidadRealizada = hechoEnEstaTarea;
                if (idCertificacionNueva != -1)
                {
                    setIdCertificacion(idCertificacionNueva);
                }
                updateStatus();
            }
            else
            {
                // debo buscar la tarea hija que esta en proceso de realizacion y ya tiene asignado
                // la certificacion en curso, o bien, esta en cero.
                CertificacionesModel *m = static_cast<CertificacionesModel*>(GlobalContainer::instance().projectLibrary(_idProyecto)->model(Tables::Certificaciones));
                idCertificacionNueva = m->idCertificacionProxima(fechaRealInicio().date(), true);

                ExecutionTaskPtr primerTareaSinCertificacion;
                ExecutionTaskPtr tareaConCertificacion;
                primerTareaSinCertificacion.clear();
                tareaConCertificacion.clear();

                foreach(ExecutionTaskPtr et, child())
                {
                    if (et->idCertificacion() == -1)
                    {
                        if (primerTareaSinCertificacion.isNull())
                        {
                            primerTareaSinCertificacion = et;
                        }
                    }
                    else if (et->idCertificacion() == idCertificacionNueva)
                    {
                        tareaConCertificacion = et;
                    }
                }
                ExecutionTaskPtr subTask = (tareaConCertificacion.isNull()) ?
                            primerTareaSinCertificacion : tareaConCertificacion;

                hechoEnEstaTarea = hechoEnEstaTarea - cantidadCertificada();
                subTask->setCantidadRealizadaEnSubTarea(hechoEnEstaTarea);
                subTask->setCantidad(_cantidad - cantidadCertificada());
                subTask->setIdCertificacion(idCertificacionNueva);
            }
        }
    }
}

bool ExecutionTask::canBeSplitted() const
{
    bool result = false;
    if (_taskType == KDGantt::TypeTask)
    {
        result = (pctCompletado() < 100.0);
    }
    return result;
}

bool ExecutionTask::isPctEditable() const
{
    bool result = false;

    if (!_isSplittedPart)
    {
        CertificacionesModel *m = static_cast<CertificacionesModel*>(GlobalContainer::instance().projectLibrary(_idProyecto)->model(Tables::Certificaciones));
        int id = m->idCertificacionProxima(fechaRealInicio().date(), true);


        if (id != -1)
        {
            CertificacionPtr c = m->cast(m->getItem(id));
            if (c->certificacionStatus() == Certificacion::CertificacionStatus::Preparacion)
                result = true;
        }
    }
    return result;
}


bool ExecutionTask::isSplittedPart() const
{
    return _isSplittedPart;
}

bool ExecutionTask::hasChild() const
{
    ExecutionTaskModel *m = static_cast<ExecutionTaskModel*>(GlobalContainer::instance().projectLibrary(_idProyecto)->model(Tables::ExecutionTasks));
    QSet<int> child = m->childIds(id());
    return child.count() > 0;
}

void ExecutionTask::setIsSplittedPart(bool value)
{
    _isSplittedPart = value;
    updateStatus();
}

QString ExecutionTask::cantidadToString() const
{
    if (!materialTask().isNull())
    {
        if (!qSharedPointerDynamicCast<Material>(materialTask())->unit().isNull())
        {
            Cantidad c(cantidad(), qSharedPointerDynamicCast<Unit>(qSharedPointerDynamicCast<Material>(materialTask())->unit()));
            return c.toString();
        }
    }
    Cantidad c(cantidad());
    return c.toString();
}

QString ExecutionTask::cantidadRealizadaToString() const
{
    if (!materialTask().isNull())
    {
        if (!qSharedPointerDynamicCast<Material>(materialTask())->unit().isNull())
        {
            Cantidad c(cantidadRealizada(), qSharedPointerDynamicCast<Unit>(qSharedPointerDynamicCast<Material>(materialTask())->unit()));
            return c.toString();
        }
    }
    Cantidad c(cantidadRealizada());
    return c.toString();
}

double ExecutionTask::rendimientoReal() const
{
    return 1;
}

void ExecutionTask::setIdCertificacion(int idCertificacion)
{
    _idCertificacion = idCertificacion;
    updateStatus();
}

bool ExecutionTask::canStart() const
{
    CertificacionesModel *m = static_cast<CertificacionesModel*>(GlobalContainer::instance().projectLibrary(_idProyecto)->model(Tables::Certificaciones));
    int id = m->idCertificacionProxima(fechaRealInicio().date(), true);
    return id >= 1;
}

int ExecutionTask::idCertificacion() const
{
    return _idCertificacion;
}

void ExecutionTask::copyDataFrom(ExecutionTaskPtr from)
{
    _idPlanningTask = from->_idPlanningTask;
    _idTareaPadre = from ->_idTareaPadre;
    _name = from->_name;
    _idMaterialTask = from->_idMaterialTask;
    _idProveedor = from->_idProveedor;
    _cantidad = from->_cantidad;
    _fechaEstimadaInicio = from->_fechaEstimadaInicio;
    _fechaEstimadaFin = from->_fechaEstimadaFin;
    _fechaRealInicio = from->_fechaRealInicio;
    _fechaRealFin = from->_fechaRealFin;
    //_pctCompletado = from->_pctCompletado;
    _taskType = from->_taskType;
    _isSplittedPart = from->_isSplittedPart;
    _idCertificacion = from->_idCertificacion;

    _idProyecto = from->_idProyecto;
    //PlanningTask *_parent;
}
