#include "executiontaskmodeladapter.h"
#include <KDGantt>
#include "models/executiontask.h"
#include "models/planningtask.h"
#include "models/material.h"
#include "models/rubro.h"
#include "models/proveedor.h"
#include "models/unit.h"
#include <cassert>
#include "models/proyecto.h"
#include "views/dlgsplitexecutiontask.h"


ExecutionTaskModelAdapter::ExecutionTaskModelAdapter(ExecutionTaskModel *model, QObject *parent) :
    QAbstractItemModel(parent)
{
    _model = model;
    connect(_model, &ExecutionTaskModel::dataChanged, this, &ExecutionTaskModelAdapter::on_model_dataChanged);
}

ExecutionTaskModelAdapter::~ExecutionTaskModelAdapter()
{
}

int ExecutionTaskModelAdapter::rowCount( const QModelIndex& idx ) const
{
    return _model->rowCount(idx);
}

int ExecutionTaskModelAdapter::columnCount( const QModelIndex& idx ) const
{
    Q_UNUSED(idx);
    return 15;
}

QModelIndex ExecutionTaskModelAdapter::index(int row, int col, const QModelIndex& parent) const
{
    ExecutionTaskModel::Node* p = parent.isValid() ?
                static_cast<ExecutionTaskModel::Node*>(parent.internalPointer())
              : _model->root();

    if (row < 0 || row >= p->childCount())
    {
        return QModelIndex();
    }
    else
    {
        return QAbstractItemModel::createIndex(row, col, p->child(row));
    }
}

QModelIndex ExecutionTaskModelAdapter::index(int idTask)
{
    return createIndex(idTask, _model->root());
}


QModelIndex ExecutionTaskModelAdapter::createIndex(int idTask, ExecutionTaskModel::Node *node)
{
    ExecutionTaskPtr pt = qSharedPointerDynamicCast<ExecutionTask>(node->entity());
    if ((node != _model->root()) && (pt->id() == idTask))
    {
        if (node == _model->root())
        {
            return QAbstractItemModel::createIndex(0, 0, node);
        }
        else
        {
            return QAbstractItemModel::createIndex(node->parent()->childNumber(node), 0, node);
        }
    }
    else
    {
        for (int i = 0; i < node->childCount(); ++i)
        {
            ExecutionTaskModel::Node *n = node->child(i);
            QModelIndex idx = createIndex(idTask, n);
            if (idx.isValid())
            {
                return idx;
            }
        }
    }
    return QModelIndex();
}

QModelIndex ExecutionTaskModelAdapter::parent(const QModelIndex& child ) const
{
    //return _model->parent(idx);
    if (!child.isValid())
        return QModelIndex();

    ExecutionTaskModel::Node* n = static_cast<ExecutionTaskModel::Node*>(child.internalPointer());
    assert(n);
    if (n == _model->root())
        return QModelIndex();

    ExecutionTaskModel::Node* p = n->parent();
    assert(p);

    if (p == _model->root())
        return QModelIndex();

    ExecutionTaskModel::Node* pp = p->parent();
    assert(pp);
    return QAbstractItemModel::createIndex(pp->childNumber(p), 0, p);
}

QVariant ExecutionTaskModelAdapter::headerData( int section, Qt::Orientation orientation, int role) const
{
    if (orientation != Qt::Horizontal || role != Qt::DisplayRole)
        return QVariant();
    switch (section)
    {
    case 0:
        return tr("Tarea");
    case 1:
        return tr("Tipo");
    case 2:
        return tr("Inicio");
    case 3:
        return tr("Fin");
    case 4:
        return tr("% Realizado");
    case 5:
        return tr("Rubro");
    case 6:
        return tr("materialTask");
    case 7:
        return tr("Proveedor");
    case 8:
        return tr("Cantidad");
    case 9:
        return tr("Duración");
    case 10:
        return tr("Costo");
    case 11:
        return tr("Precio");
    case 12:
        return tr("Fecha Inicio Planificada");
    case 13:
        return tr("Fecha Finalizacion Planificada");
    default:
        return QVariant();
    }
}

QVariant ExecutionTaskModelAdapter::data( const QModelIndex& idx, int role) const
{
    if (!idx.isValid())
        return QVariant();

    ExecutionTaskModel::Node* n = static_cast<ExecutionTaskModel::Node*>(idx.internalPointer());

    if (_model->rowCount() == 0)
        return QVariant();

    //PlanningTaskPtr p = qSharedPointerDynamicCast<PlanningTask>(_model->getItemByRowid(idx.row()));
    ExecutionTaskPtr p = qSharedPointerDynamicCast<ExecutionTask>(n->entity());

    if (idx.column() == 0)
    {
        switch (role)
        {
        case Qt::DisplayRole:
        case Qt::EditRole:
            return p->name();
        case KDGantt::TextPositionRole:
            return KDGantt::StyleOptionGanttItem::Right;
        }
    }
    else if (idx.column() == 1)
    {
        switch (role)
        {
        case Qt::DisplayRole:
        case Qt::EditRole:
            return qVariantFromValue<int>(p->taskType());
            //return qVariantFromValue<int>(KDGantt::TypeTask);
        }
    }
    else if (idx.column() == 2)
    {
        switch (role)
        {
        case Qt::DisplayRole:
            return p->fechaRealInicio().date().toString();
        case Qt::EditRole:
        case KDGantt::StartTimeRole:
            return p->fechaRealInicio();
        }
    }
    else if (idx.column() == 3)
    {
        switch (role)
        {
        case Qt::DisplayRole:
            return p->fechaRealFin().date().toString();
        case Qt::EditRole:
        case KDGantt::EndTimeRole:
            return p->fechaRealFin();
        }
    }
    else if (idx.column() == 4)
    {
        switch (role)
        {
        case Qt::DisplayRole:
        case Qt::EditRole:
            return p->pctCompletado();
        }
    }
    else if (idx.column() == 5 && role == Qt::DisplayRole)
    {
        if (p->idMaterialTask() != -1)
        {
            MaterialPtr m = qSharedPointerDynamicCast<Material>(p->materialTask());
            if (m->idRubro() != -1)
            {
                RubroPtr r = qSharedPointerDynamicCast<Rubro>(m->rubro());
                if (!r.isNull())
                    return r->name();
            }
        }
    }
    else if (idx.column() == 6 && role == Qt::DisplayRole)
    {
        if (p->idMaterialTask() != -1)
        {
            MaterialPtr m = qSharedPointerDynamicCast<Material>(p->materialTask());
            return m->name();
        }
    }
    else if (idx.column() == 7 && role == Qt::DisplayRole)
    {
        if (p->idProveedor() != -1)
        {
            ProveedorPtr pp = qSharedPointerDynamicCast<Proveedor>(p->proveedor());
            return pp->name();
        }
    }
    else if (idx.column() == 8)
    {
        switch (role)
        {
        case Qt::DisplayRole:
            return p->cantidadToString();
        case Qt::EditRole:
            return p->cantidad();
        }
    }
    else if (idx.column() == 9 && role == Qt::DisplayRole)
    {
        return p->duracion();
    }
    else if (idx.column() == 10 && role == Qt::DisplayRole)
    {
        return p->costo();
    }
    else if (idx.column() == 11 && role == Qt::DisplayRole)
    {
        return p->precio();
    }
    else if (idx.column() == 12 && role == Qt::DisplayRole)
    {
        return p->fechaEstimadaInicio().date().toString();
    }
    else if (idx.column() == 13 && role == Qt::DisplayRole)
    {
        return p->fechaEstimadaFin().date().toString();
    }

    if (role == Qt::ToolTipRole)
    {
        return p->tooltip();
    }
    return QVariant();
}


bool ExecutionTaskModelAdapter::setData( const QModelIndex& idx,  const QVariant& value, int role)
{
    if (!idx.isValid())
        return false;

    qDebug() << "ProjectModel::setData" << idx.column() << role << value;

    ExecutionTaskModel::Node* n = static_cast<ExecutionTaskModel::Node*>(idx.internalPointer());
    //PlanningTaskPtr p = qSharedPointerDynamicCast<PlanningTask>(_model->getItemByRowid(idx.row()));
    ExecutionTaskPtr p = qSharedPointerDynamicCast<ExecutionTask>(n->entity());


    if (idx.column() == 0)
    {
        switch ( role ) {
        case Qt::DisplayRole:
        case Qt::EditRole:
            p->setName(value.toString());
            break;
        case KDGantt::TextPositionRole:
//            n->setPosition( static_cast<KDGantt::StyleOptionGanttItem::Position>(value.toInt()) );
            break;
        }
    }
    else if (idx.column() == 1)
    {
        switch (role)
        {
        case Qt::DisplayRole:
        case Qt::EditRole:
            //n->setType( value.toInt() );
            break;
        }
    }
    else if ( idx.column() == 2 )
    {
        switch (role)
        {
        case Qt::DisplayRole:
        case Qt::EditRole:
        case KDGantt::StartTimeRole:
            QDateTime date = value.toDateTime();
            p->setFechaRealInicio(date);
            break;
        }
    }
    else if (idx.column() == 3)
    {
        switch (role)
        {
        case Qt::DisplayRole:
        case Qt::EditRole:
        case KDGantt::EndTimeRole:
            QDateTime date = value.toDateTime();
            p->setFechaRealFin(date);
            break;
        }
    }
    else if (idx.column() == 4)
    {
        switch ( role )
        {
        case Qt::DisplayRole:
        case Qt::EditRole:
            p->setPctCompletado(value.toDouble());
            //n->setCompletion(value.toInt());
            break;
        }
    }
    else if (idx.column() == 8)
    {
        switch (role)
        {
        case Qt::DisplayRole:
        case Qt::EditRole:
            p->setCantidad(value.toDouble());
        }
    }
    emit dataChanged(idx, idx);
    return true;
}

bool ExecutionTaskModelAdapter::insertRows( int row, int count, const QModelIndex& parent)
{
    beginInsertRows(parent, row, row + count - 1);
    ExecutionTaskModel::Node* p = _model->root();
    bool canCreate = true;
    int idTareaPadre = -1;
    if (parent.isValid())
    {
        p = static_cast<ExecutionTaskModel::Node*>(parent.internalPointer());
        if (!p->entity().isNull())
        {
            ExecutionTaskPtr pt = qSharedPointerDynamicCast<ExecutionTask>(p->entity());
            canCreate = ((pt->taskType() == KDGantt::TypeSummary) || (pt->taskType() == KDGantt::TypeMulti));
            idTareaPadre = pt->id();
        }
    }
    assert( p );
    if (canCreate)
    {
        for (int i = 0; i < count; ++i )
        {
            EntityBasePtr e = _model->createEntity();
            ExecutionTaskModel::Node* n = new ExecutionTaskModel::Node(e);
            qSharedPointerDynamicCast<ExecutionTask>(e)->setIdTareaPadre(idTareaPadre);
            p->insertChild(row + i, n);
        }
    }
    endInsertRows();
    return canCreate;
}

bool ExecutionTaskModelAdapter::removeRow(int row, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row);
    ExecutionTaskModel::Node *parentNode = _model->root();
    if (parent.isValid())
    {
        parentNode = static_cast<ExecutionTaskModel::Node*>(parent.internalPointer());
    }
    parentNode->removeChild(parentNode->child(row));
    endRemoveRows();
    return true;
}

Qt::ItemFlags ExecutionTaskModelAdapter::flags( const QModelIndex& idx) const
{
    ProyectoPtr p = qSharedPointerDynamicCast<Proyecto>(_proyecto);
    Qt::ItemFlags f = QAbstractItemModel::flags(idx);

    if (!p.isNull() && p->projectStatus() == Proyecto::ProjectStatus::Ejecucion)
    {
        ExecutionTaskModel::Node *node = static_cast<ExecutionTaskModel::Node*>(idx.internalPointer());
        ExecutionTaskPtr et = qSharedPointerDynamicCast<ExecutionTask>(node->entity());
        if (et->pctCompletado() == 0.)
        {
            if (idx.column() == 4)
            {
                if (et->canStart())
                {
                    f |= Qt::ItemIsEditable;
                }
            }
            else
            {
                f |= Qt::ItemIsEditable;
            }
        }
        else
        {
            if (et->pctCompletado() < 100.)
            {
                switch (idx.column())
                {
                case 3:
                case 4:
                    f |= Qt::ItemIsEditable;
                    break;
                default:
                    break;
                }
            }
        }
    }
    return f;
}

void ExecutionTaskModelAdapter::editEntity(int row)
{
    ExecutionTaskModel::Node* n = _model->root()->child(row);

    //PlanningTaskPtr p = qSharedPointerDynamicCast<PlanningTask>(_model->getItemByRowid(idx.row()));
    ExecutionTaskPtr p = qSharedPointerDynamicCast<ExecutionTask>(n->entity());
    _model->editEntity(p);

    //_model->editEntity(row);

    QModelIndex idx = index(row, 0);
    emit dataChanged(idx, idx);
}

void ExecutionTaskModelAdapter::editEntity(QModelIndex index)
{
    if (index.isValid())
    {
        ExecutionTaskModel::Node* n = static_cast<ExecutionTaskModel::Node*>(index.internalPointer());
        //PlanningTaskPtr p = qSharedPointerDynamicCast<PlanningTask>(_model->getItemByRowid(idx.row()));
        ExecutionTaskPtr p = qSharedPointerDynamicCast<ExecutionTask>(n->entity());
        _model->editEntity(p);
    }
}

void ExecutionTaskModelAdapter::removeEntity(QWidget *, QModelIndex &index)
{
    removeRow(index.row(), index.parent());
    //_model->removeEntity(parent, index);
}

bool ExecutionTaskModelAdapter::canCreateEntity() const
{
    return _model->canCreateEntity();
}

bool ExecutionTaskModelAdapter::canBeSplitted(QModelIndex &index) const
{
    bool result = false;
    if (index.isValid())
    {
        ExecutionTaskModel::Node *n = static_cast<ExecutionTaskModel::Node*>(index.internalPointer());
        ExecutionTaskPtr p = qSharedPointerDynamicCast<ExecutionTask>(n->entity());
        result = p->canBeSplitted();
    }
    return result;
}

void ExecutionTaskModelAdapter::splitTaskNotSplitted(ExecutionTaskModel::Node *node, bool useDialog, const QDate &date)
{
    ExecutionTaskPtr tp = qSharedPointerDynamicCast<ExecutionTask>(node->entity());

    QDate dt = date;
    double pct;
    bool performSplit = false;
    if (useDialog)
    {
        DlgSplitExecutionTask dlg;
        dlg.setPct(tp->pctCompletado());
        dlg.setExecutionTask(tp);
        dlg.setCantidadTotal(tp->cantidad());
        dlg.setCantidadRealizada(0.);

        dlg.setDate(dt);
        if (dlg.exec() == QDialog::Accepted)
        {
            performSplit = true;

            dt = dlg.date();
            pct = dlg.pct();
        }
    }
    else
    {
        performSplit = true;
    }

    if (performSplit)
    {
        EntityBasePtr e1 = _model->createEntity();
        ExecutionTaskModel::Node *n1 = new ExecutionTaskModel::Node(e1);
        ExecutionTaskPtr et1 = qSharedPointerDynamicCast<ExecutionTask>(e1);
        et1->copyDataFrom(tp);
        et1->setIdCertificacion(tp->idCertificacion());
        et1->setIdTareaPadre(tp->id());
        et1->setPctCompletado(100);
        et1->setCantidad(pct * tp->cantidad() / 100.0);
        QDateTime dt2 = QDateTime(tp->fechaRealInicio().date(), QTime(12, 0, 0, 0));
        et1->setFechaRealInicio(dt2);
        et1->setFechaEstimadaInicio(dt2);
        et1->setFechaEstimadaFin(QDateTime(dt, QTime(12, 0, 0, 0)));
        et1->setFechaRealFin(QDateTime(dt, QTime(12, 0, 0, 0)));
        et1->setIsSplittedPart(true);
        node->addChild(n1);

        EntityBasePtr e2 = _model->createEntity();
        ExecutionTaskModel::Node *n2 = new ExecutionTaskModel::Node(e2);
        ExecutionTaskPtr et2 = qSharedPointerDynamicCast<ExecutionTask>(e2);
        et2->copyDataFrom(tp);
        et2->setIdTareaPadre(tp->id());

        et2->setFechaRealInicio(QDateTime(dt, QTime(12, 0, 0, 0)));
        et2->setFechaEstimadaInicio(QDateTime(dt, QTime(12, 0, 0, 0)));

        QDateTime dt3 = tp->fechaRealFin();
        if (dt3.date() <= dt)
        {
            dt3.setDate(dt.addDays(1));
        }
        et2->setFechaRealFin(dt3);
        et2->setFechaEstimadaFin(dt3);
        et2->setIsSplittedPart(true);
        et2->setCantidad(tp->cantidad() - et1->cantidad());
        et2->setIdCertificacion(-1);
        et2->setPctCompletado(0.);
        node->addChild(n2);

        tp->setTaskType(KDGantt::TypeMulti);
        tp->setIdCertificacion(-1);
    }
}

void ExecutionTaskModelAdapter::splitTaskSplitted(ExecutionTaskModel::Node *node, bool useDialog, const QDate &date)
{
    DlgSplitExecutionTask dlg;

    ExecutionTaskPtr tp = qSharedPointerDynamicCast<ExecutionTask>(node->entity());

    dlg.setPct(tp->pctCompletado());
    dlg.setExecutionTask(tp);
    double cantTotal = 0.;
    double cantRealizada = 0.;
    for (int i = 0; i < node->childCount(); ++i)
    {
        ExecutionTaskPtr t = qSharedPointerDynamicCast<ExecutionTask>(node->child(i)->entity());
        cantTotal += t->cantidad();
        if (t->pctCompletado() == 100.0)
        {
            cantRealizada += t->cantidad();
        }
    }

    QDate dt = QDate::currentDate();
    dlg.setDate(dt);
    dlg.setCantidadTotal(cantTotal);
    dlg.setCantidadRealizada(cantRealizada);
    double pctAcumulado = 100.0 * cantRealizada / cantTotal;
    dlg.setPct(pctAcumulado);
    if (dlg.exec() == QDialog::Accepted)
    {
        dt = dlg.date();
        EntityBasePtr e1 = node->child(node->childCount() - 1)->entity();
        double cantidadParcial = dlg.pct() * cantTotal - cantRealizada;
        ExecutionTaskPtr et1 = qSharedPointerDynamicCast<ExecutionTask>(e1);
        et1->setCantidad(cantidadParcial);
        et1->setPctCompletado(100);
        QDateTime dt2 = tp->fechaRealInicio();
        et1->setFechaEstimadaFin(QDateTime(dt, QTime(12, 0, 0, 0)));
        et1->setFechaRealFin(QDateTime(dt, QTime(12, 0, 0, 0)));
        et1->setIsSplittedPart(true);

        EntityBasePtr e2 = _model->createEntity();
        ExecutionTaskModel::Node *n2 = new ExecutionTaskModel::Node(e2);
        ExecutionTaskPtr et2 = qSharedPointerDynamicCast<ExecutionTask>(e2);
        et2->setIdTareaPadre(tp->id());
        et2->setFechaRealInicio(QDateTime(dt, QTime(12, 0, 0, 0)));
        et2->setFechaEstimadaInicio(QDateTime(dt, QTime(12, 0, 0, 0)));
        et2->setIdCertificacion(-1);

        QDateTime dt3 = tp->fechaRealFin();
        et2->setFechaRealFin(dt3);
        et2->setFechaEstimadaFin(dt3);
        et2->setIsSplittedPart(true);
        et2->setCantidad(cantTotal * 1 - dlg.pct() / 100.0);
        node->addChild(n2);

        tp->setTaskType(KDGantt::TypeMulti);
    }
}

void ExecutionTaskModelAdapter::splitTask(QModelIndex &index)
{
    if (canBeSplitted(index))
    {
        //DlgSplitExecutionTask dlg;

        ExecutionTaskModel::Node* n = static_cast<ExecutionTaskModel::Node*>(index.internalPointer());
        ExecutionTaskPtr tp = qSharedPointerDynamicCast<ExecutionTask>(n->entity());
        if (tp->isSplittedPart())
        {
            n = n->parent();
            splitTaskSplitted(n, true, QDate::currentDate());
        }
        else
        {
            splitTaskNotSplitted(n, true, QDate::currentDate());
        }
    }
    emit dataChanged(index, index);
}

void ExecutionTaskModelAdapter::splitTask(EntityBasePtr execTask, const QDate &fecha)
{
    ExecutionTaskPtr et = qSharedPointerDynamicCast<ExecutionTask>(execTask);
    if (et->canBeSplitted())
    {
        QModelIndex idx = index(et->id());
        ExecutionTaskModel::Node* n = static_cast<ExecutionTaskModel::Node*>(idx.internalPointer());
        if (et->isSplittedPart())
        {
            n = n->parent();
            splitTaskSplitted(n, false, fecha);
        }
        else
        {
            splitTaskNotSplitted(n, false, fecha);
        }
    }
}

EntityBasePtr ExecutionTaskModelAdapter::itemByRowId(int row)
{
    return _model->getItemByRowid(row);
}

int ExecutionTaskModelAdapter::idFromPlanning(int idPlanningTask)
{
    return _model->idFromPlanning(idPlanningTask);
}

void ExecutionTaskModelAdapter::setProyecto(EntityBasePtr proyecto)
{
    _proyecto = proyecto;
}

void ExecutionTaskModelAdapter::on_model_dataChanged(const QModelIndex &, const QModelIndex &, const QVector<int> &)
{
    emit dataChanged(QModelIndex(), QModelIndex());
}

IModel* ExecutionTaskModelAdapter::innerModel() const
{
    return _model;
}
