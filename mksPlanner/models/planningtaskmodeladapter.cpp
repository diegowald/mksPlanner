#include "planningtaskmodeladapter.h"
#include <KDGantt>
#include "models/planningtask.h"
#include "models/material.h"
#include "models/rubro.h"
#include "models/proveedor.h"
#include "models/unit.h"


PlanningTaskModelAdapter::PlanningTaskModelAdapter(PlanningTaskModel *model, QObject *parent) :
    QAbstractItemModel(parent)
{
    _model = model;
}

PlanningTaskModelAdapter::~PlanningTaskModelAdapter()
{
}

int PlanningTaskModelAdapter::rowCount( const QModelIndex& idx ) const
{
    if ( idx.isValid() )
        return 0; // static_cast<Node*>( idx.internalPointer() )->childCount();
    else
        return _model->rowCount(idx);
}

int PlanningTaskModelAdapter::columnCount( const QModelIndex& idx ) const
{
    Q_UNUSED(idx);
    return 13; //_model->columnCount(idx);
}

QModelIndex PlanningTaskModelAdapter::index( int row, int col, const QModelIndex& parent) const
{
    /*Node* p = m_root;
    if ( parent.isValid() ) {
        p = static_cast<Node*>( parent.internalPointer() );
    }
    if ( row < 0 || row >= p->childCount() ) return QModelIndex();
    else return createIndex( row, col, p->child( row ) );*/
    return createIndex(row, col);
}


QModelIndex PlanningTaskModelAdapter::parent( const QModelIndex& idx ) const
{
    /*if ( !idx.isValid() ) return QModelIndex();

    Node* n = static_cast<Node*>( idx.internalPointer() );
    assert( n );
    Node* p = n->parent();
    if ( p==m_root )return QModelIndex();

    Node* pp = p->parent();
    assert( pp );
    return createIndex( pp->childNumber( p ), 0, p );*/
    return QModelIndex();
}

QVariant PlanningTaskModelAdapter::headerData( int section, Qt::Orientation orientation, int role) const
{
    if (orientation != Qt::Horizontal || role != Qt::DisplayRole)
        return QVariant();
    switch (section)
    {
    case 0:
        return tr("Name");
    case 1:
        return tr("Type");
    case 2:
        return tr("Start");
    case 3:
        return tr("End");
    case 4:
        return tr("Completion %");
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

    //Node* n = static_cast<Node*>( idx.internalPointer() );
    if (_model->rowCount() == 0)
        return QVariant();

    PlanningTaskPtr p = qSharedPointerDynamicCast<PlanningTask>(_model->getItemByRowid(idx.row()));

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
            return qVariantFromValue<int>(KDGantt::TypeTask);
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
/*    else if (idx.column() == 5)
    {
        switch (role)
        {
        case Qt::DisplayRole:
        case Qt::EditRole:
            return p->name();
        case KDGantt::ItemTypeRole:
            return KDGantt::TypeTask;
        case KDGantt::StartTimeRole:
            return p->fechaEstimadaInicio();
        case KDGantt::EndTimeRole:
            return p->fechaEstimadaFin();
        case KDGantt::TaskCompletionRole:
            return QVariant();
            break;
        }
    }
    */
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
    return QVariant();
}


bool PlanningTaskModelAdapter::setData( const QModelIndex& idx,  const QVariant& value, int role)
{
/*    if (!idx.isValid())
        return false;*/

    qDebug() << "ProjectModel::setData" << idx.column() << role << value;

    //Node* n = static_cast<Node*>( idx.internalPointer() );
    PlanningTaskPtr p = qSharedPointerDynamicCast<PlanningTask>(_model->getItemByRowid(idx.row()));


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
    beginInsertRows( parent, row, row+count-1 );
    _model->insertRows(row, count, parent);
    /*Node* p = m_root;
    if ( parent.isValid() ) p = static_cast<Node*>( parent.internalPointer() );
    assert( p );

    for ( int i = 0; i < count; ++i ) {
        Node* n = new Node;
        p->insertChild( row+i, n );
    }*/
    endInsertRows();
    return true;
}

Qt::ItemFlags PlanningTaskModelAdapter::flags( const QModelIndex& idx) const
{
    return QAbstractItemModel::flags( idx ) | Qt::ItemIsEditable;
}

void PlanningTaskModelAdapter::editEntity(int row)
{
    _model->editEntity(row);

    QModelIndex idx = createIndex(row, 0);
    /*setData(idx, QVariant());*/
    emit dataChanged(idx, idx);
    //emit dataChanged(idx, idx);
}

void PlanningTaskModelAdapter::removeEntity(QWidget *parent, int row)
{
    removeEntity(parent, row);
}
