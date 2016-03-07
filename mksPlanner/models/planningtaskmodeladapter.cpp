#include "planningtaskmodeladapter.h"
#include <KDGantt>
#include "models/planningtask.h"
#include "models/material.h"
#include "models/rubro.h"
#include "models/proveedor.h"
#include "models/unit.h"
#include <cassert>
#include "models/proyecto.h"


PlanningTaskModelAdapter::PlanningTaskModelAdapter(PlanningTaskModel *model, QObject *parent) :
    QAbstractItemModel(parent)
{
    _model = model;
    _proyecto.clear();
}

PlanningTaskModelAdapter::~PlanningTaskModelAdapter()
{
}

int PlanningTaskModelAdapter::rowCount( const QModelIndex& idx ) const
{
    return _model->rowCount(idx);
}

int PlanningTaskModelAdapter::columnCount( const QModelIndex& idx ) const
{
    Q_UNUSED(idx);
    return 13;
}

QModelIndex PlanningTaskModelAdapter::index(int row, int col, const QModelIndex& parent) const
{
    PlanningTaskModel::Node* p = parent.isValid() ?
                static_cast<PlanningTaskModel::Node*>(parent.internalPointer())
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

QModelIndex PlanningTaskModelAdapter::index(int idTask)
{
    return createIndex(idTask, _model->root());
}


QModelIndex PlanningTaskModelAdapter::createIndex(int idTask, PlanningTaskModel::Node *node)
{
    PlanningTaskPtr pt = qSharedPointerDynamicCast<PlanningTask>(node->entity());
    if ((node != _model->root()) && (pt->id() == idTask))
    {
        if (node == _model->root())
        {
            return QAbstractItemModel::createIndex(0, 0, node);
        }
        else
        {
            return QAbstractItemModel::createIndex(node->parent()->childNumber(node), 0, this);
        }
    }
    else
    {
        for (int i = 0; i < node->childCount(); ++i)
        {
            PlanningTaskModel::Node *n = node->child(i);
            QModelIndex idx = createIndex(idTask, n);
            if (idx.isValid())
            {
                return idx;
            }
        }
    }
    return QModelIndex();
}

QModelIndex PlanningTaskModelAdapter::parent(const QModelIndex& child ) const
{
    //return _model->parent(idx);
    if (!child.isValid())
        return QModelIndex();

    PlanningTaskModel::Node* n = static_cast<PlanningTaskModel::Node*>(child.internalPointer());
    assert(n);
    if (n == _model->root())
        return QModelIndex();

    PlanningTaskModel::Node* p = n->parent();
    assert(p);

    if (p == _model->root())
        return QModelIndex();

    PlanningTaskModel::Node* pp = p->parent();
    assert(pp);
    return QAbstractItemModel::createIndex(pp->childNumber(p), 0, p);
}

QVariant PlanningTaskModelAdapter::headerData( int section, Qt::Orientation orientation, int role) const
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
        return tr("Inicio Estimado");
    case 3:
        return tr("Fin Estimado");
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
        return tr("Unidad de medida");
    case 10:
        return tr("Duración");
    case 11:
        return tr("Costo");
    case 12:
        return tr("Precio");

    default:
        return QVariant();
    }
}

QVariant PlanningTaskModelAdapter::data( const QModelIndex& idx, int role) const
{
    if (!idx.isValid())
        return QVariant();

    PlanningTaskModel::Node* n = static_cast<PlanningTaskModel::Node*>(idx.internalPointer());

    if (_model->rowCount() == 0)
        return QVariant();

    //PlanningTaskPtr p = qSharedPointerDynamicCast<PlanningTask>(_model->getItemByRowid(idx.row()));
    PlanningTaskPtr p = qSharedPointerDynamicCast<PlanningTask>(n->entity());

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
            return p->fechaEstimadaInicio().date().toString();
        case Qt::EditRole:
        case KDGantt::StartTimeRole:
            return p->fechaEstimadaInicio();
        }
    }
    else if (idx.column() == 3)
    {
        switch (role)
        {
        case Qt::DisplayRole:
            return p->fechaEstimadaFin().date().toString();
        case Qt::EditRole:
        case KDGantt::EndTimeRole:
            return p->fechaEstimadaFin();
        }
    }
    else if (idx.column() == 4)
    {
        switch (role)
        {
        case Qt::DisplayRole:
        case Qt::EditRole:
            return QVariant();
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
        case Qt::EditRole:
            return p->cantidad();
        }
    }
    else if (idx.column() == 9 && role == Qt::DisplayRole)
    {
        if (p->idMaterialTask() != -1)
        {
            MaterialPtr m = qSharedPointerDynamicCast<Material>(p->materialTask());
            if (m->idUnit() != -1)
            {
                UnitPtr unit = qSharedPointerDynamicCast<Unit>(m->unit());
                return unit->name();
            }
        }
    }
    else if (idx.column() == 10 && role == Qt::DisplayRole)
    {
        return p->duracion();
    }
    else if (idx.column() == 11 && role == Qt::DisplayRole)
    {
        return p->costo();
    }
    else if (idx.column() == 12 && role == Qt::DisplayRole)
    {
        return p->precio();
    }

    if (role == Qt::ToolTipRole)
    {
        return p->tooltip();
    }
    return QVariant();
}


bool PlanningTaskModelAdapter::setData( const QModelIndex& idx,  const QVariant& value, int role)
{
    if (!idx.isValid())
        return false;

    qDebug() << "ProjectModel::setData" << idx.column() << role << value;

    PlanningTaskModel::Node* n = static_cast<PlanningTaskModel::Node*>(idx.internalPointer());
    //PlanningTaskPtr p = qSharedPointerDynamicCast<PlanningTask>(_model->getItemByRowid(idx.row()));
    PlanningTaskPtr p = qSharedPointerDynamicCast<PlanningTask>(n->entity());


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
            p->setFechaEstimadaInicio(date);
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
            p->setFechaEstimadaFin(date);
            break;
        }
    }
    else if (idx.column() == 4)
    {
        switch ( role )
        {
        case Qt::DisplayRole:
        case Qt::EditRole:
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

bool PlanningTaskModelAdapter::insertRows( int row, int count, const QModelIndex& parent)
{
    beginInsertRows(parent, row, row + count - 1);
    PlanningTaskModel::Node* p = _model->root();
    bool canCreate = true;
    int idTareaPadre = -1;
    if (parent.isValid())
    {
        p = static_cast<PlanningTaskModel::Node*>(parent.internalPointer());
        if (!p->entity().isNull())
        {
            PlanningTaskPtr pt = qSharedPointerDynamicCast<PlanningTask>(p->entity());
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
            PlanningTaskModel::Node* n = new PlanningTaskModel::Node(e);
            qSharedPointerDynamicCast<PlanningTask>(e)->setIdTareaPadre(idTareaPadre);
            p->insertChild(row + i, n);
        }
    }
    endInsertRows();
    return canCreate;
}

bool PlanningTaskModelAdapter::removeRow(int row, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row);
    PlanningTaskModel::Node *parentNode = _model->root();
    if (parent.isValid())
    {
        parentNode = static_cast<PlanningTaskModel::Node*>(parent.internalPointer());
    }
    parentNode->removeChild(parentNode->child(row));
    endRemoveRows();
}

Qt::ItemFlags PlanningTaskModelAdapter::flags( const QModelIndex& idx) const
{
    ProyectoPtr p = qSharedPointerDynamicCast<Proyecto>(_proyecto);

    Qt::ItemFlags f = QAbstractItemModel::flags(idx);
    if (!p.isNull() && p->projectStatus() == Proyecto::ProjectStatus::Planificacion)
    {
        f |= Qt::ItemIsEditable;
    }
    return f;
}

void PlanningTaskModelAdapter::editEntity(int row)
{
    _model->editEntity(row);

    QModelIndex idx = index(row, 0);
    emit dataChanged(idx, idx);
}

void PlanningTaskModelAdapter::editEntity(QModelIndex index)
{
    if (index.isValid())
    {
        PlanningTaskModel::Node* n = static_cast<PlanningTaskModel::Node*>(index.internalPointer());
        //PlanningTaskPtr p = qSharedPointerDynamicCast<PlanningTask>(_model->getItemByRowid(idx.row()));
        PlanningTaskPtr p = qSharedPointerDynamicCast<PlanningTask>(n->entity());
        _model->editEntity(p);
    }
}

void PlanningTaskModelAdapter::removeEntity(QWidget *parent, QModelIndex &index)
{
    removeRow(index.row(), index.parent());
    //_model->removeEntity(parent, index);
}

bool PlanningTaskModelAdapter::canCreateEntity() const
{
    return _model->canCreateEntity();
}

EntityBasePtr PlanningTaskModelAdapter::itemByRowId(int row)
{
    return _model->getItemByRowid(row);
}

void PlanningTaskModelAdapter::setProyecto(EntityBasePtr entity)
{
    _proyecto = entity;
}
