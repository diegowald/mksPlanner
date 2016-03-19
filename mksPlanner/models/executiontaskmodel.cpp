#include "executiontaskmodel.h"
#include <QSharedPointer>
#include <QDate>
#include "models/executiontask.h"
#include "models/material.h"
#include "models/rubro.h"
#include "models/proveedor.h"
#include <KDGantt>
#include <models/unit.h>
#include "globalcontainer.h"
#include <cassert>
#include <QMap>
#include "models/planningtaskmodel.h"
#include "models/planningtask.h"
#include "views/dlgeditexecutiontask.h"

/* NODE */

ExecutionTaskModel::Node::Node(EntityBasePtr entity, Node *parent)
{
    _parent = parent;
    _entity = entity;
    _id = (_entity.isNull()) ? -1 : _entity->id();
    if (_parent)
    {
        _parent->addChild(this);
    }
}

void ExecutionTaskModel::Node::addChild(Node *node)
{
    node->setParent(this);
    _children.append(node);
}

ExecutionTaskModel::Node::~Node()
{
    while (!_children.isEmpty())
    {
        ExecutionTaskModel::Node *node = _children.front();
        delete node;
        _children.pop_front();
    }
    //if (_parent) _parent->removeChild(this);
}

void ExecutionTaskModel::Node::insertChild( int i, Node* node)
{
    node->setParent(this);
    _children.insert(i, node);
}

bool ExecutionTaskModel::Node::createChild(EntityBasePtr entity)
{
    ExecutionTaskPtr p = qSharedPointerDynamicCast<ExecutionTask>(entity);
    if (_id == p->idTareaPadre())
    {
        Node *n = new Node(entity, this);
        (void)n;
        //addChild(n);
        return true;
    }
    else
    {
        foreach (Node *n, _children)
        {
            if (n->createChild(entity))
                return true;
        }
    }
    return false;
}

void ExecutionTaskModel::Node::removeChild( Node* node)
{
    if (!node->entity().isNull())
        node->_entity->deleteEntity();
    _children.removeOne(node);
    delete node;
}

ExecutionTaskModel::Node* ExecutionTaskModel::Node::parent() const
{
    return _parent;
}

void ExecutionTaskModel::Node::setParent(Node *parent)
{
    _parent = parent;
}

int ExecutionTaskModel::Node::childCount() const
{
    return _children.count();
}

int ExecutionTaskModel::Node::childNumber(Node* n) const
{
    return _children.indexOf(n);
}

ExecutionTaskModel::Node* ExecutionTaskModel::Node::child(int i) const
{
    return _children.at(i);
}

EntityBasePtr ExecutionTaskModel::Node::entity() const
{
    return _entity;
}

/* /NODE */

ExecutionTaskModel::ExecutionTaskModel(int idProyecto, QObject *parent)
    : ModelBase(Tables::PlanningTasks, "executiontasks", false, "proyectos", parent)
{
    _idProyecto = idProyecto;
    defineColumnNames();
    addDependency(static_cast<int>(Tables::Tareas));
    addDependency(static_cast<int>(Tables::Rubros));
    addDependency(static_cast<int>(Tables::Unidades));
    addDependency(static_cast<int>(Tables::Proveedores));
    //addDependency(static_cast<int>(Tables::PlanningTasks));
    _root = new Node(EntityBasePtr(), NULL);
}

void ExecutionTaskModel::defineColumnNames()
{
    setField(1, "idTareaPadre",
             [&] (EntityBasePtr entity, int role) -> QVariant
    {
        QVariant v;
        switch (role)
        {
        case Qt::DisplayRole:
        case Qt::EditRole:
            v = cast(entity)->idTareaPadre();
            break;
        default:
            v = QVariant();
        }
        return v;
    },
    [&] (EntityBasePtr entity, const QVariant& value, int role) ->bool
    {
        if (role == Qt::EditRole)
        {
            cast(entity)->setIdTareaPadre(value.toInt());
            return true;
        }
        else
        {
            return false;
        }
    });

    setField(2, "idMaterialTask",
             [&] (EntityBasePtr entity, int role) -> QVariant
    {
        QVariant v;
        switch (role)
        {
        case Qt::DisplayRole:
        case Qt::EditRole:
            v = cast(entity)->idMaterialTask();
            break;
        default:
            v = QVariant();
        }
        return v;
    },
    [&] (EntityBasePtr entity, const QVariant& value, int role) ->bool
    {
        if (role == Qt::EditRole)
        {
            cast(entity)->setIdMaterialTask(value.toInt());
            return true;
        }
        else
        {
            return false;
        }
    });

    setField(3, "idProveedor",
             [&] (EntityBasePtr entity, int role) -> QVariant
    {
        QVariant v;
        switch (role)
        {
        case Qt::DisplayRole:
        case Qt::EditRole:
            v = cast(entity)->idProveedor();
            break;
        default:
            v = QVariant();
        }
        return v;
    },
    [&] (EntityBasePtr entity, const QVariant& value, int role) ->bool
    {
        if (role == Qt::EditRole)
        {
            cast(entity)->setIdProveedor(value.toInt());
            return true;
        }
        else
        {
            return false;
        }
    });

    setField(4, "tareaPadre",
             [&] (EntityBasePtr entity, int role) -> QVariant
    {
        QVariant v;
        switch (role)
        {
        case Qt::DisplayRole:
        case Qt::EditRole:
            if (cast(entity)->idTareaPadre() != -1)
            {
                v = cast(cast(entity)->tareaPadre())->name();
            }
            else
            {
                v = QVariant();
            }
            break;
        default:
            v = QVariant();
        }
        return v;
    });

    setField(5, "Tarea",
             [&] (EntityBasePtr entity, int role) -> QVariant
    {
        QVariant v;
        switch (role)
        {
        case Qt::DisplayRole:
        case Qt::EditRole:
            v = cast(entity)->name();
            break;
        default:
            v = QVariant();
        }
        return v;
    },
    [&] (EntityBasePtr entity, const QVariant& value, int role) ->bool
    {
        if (role == Qt::EditRole)
        {
            cast(entity)->setName(value.toString());
            return true;
        }
        else
        {
            return false;
        }
    });

    setField(6, "Rubro",
             [&] (EntityBasePtr entity, int role) -> QVariant
    {
        QVariant v;
        switch (role)
        {
        case Qt::DisplayRole:
        case Qt::EditRole:
            if (cast(entity)->idMaterialTask() != -1)
            {
                v = qSharedPointerDynamicCast<Material>(cast(entity)->materialTask())->name();
            }
            else
            {
                v = QVariant();
            }
            break;
        default:
            v = QVariant();
        }
        return v;
    });

    setField(7, "materialTask",
             [&] (EntityBasePtr entity, int role) -> QVariant
    {
        QVariant v;
        switch (role)
        {
        case Qt::DisplayRole:
        case Qt::EditRole:
            if (cast(entity)->idMaterialTask() != -1)
            {
                v = qSharedPointerDynamicCast<Material>(cast(entity)->materialTask())->name();
            }
            else
            {
                v = QVariant();
            }
            break;
        default:
            v = QVariant();
        }
        return v;
    });

    setField(8, "Proveedor",
             [&] (EntityBasePtr entity, int role) -> QVariant
    {
        QVariant v;
        switch (role)
        {
        case Qt::DisplayRole:
        case Qt::EditRole:
            if (cast(entity)->idProveedor() != -1)
            {
                v = qSharedPointerDynamicCast<Proveedor>(cast(entity)->proveedor())->name();
            }
            else
            {
                v = QVariant();
            }
            break;
        default:
            v = QVariant();
        }
        return v;
    });

    setField(9, "Cantidad",
             [&] (EntityBasePtr entity, int role) -> QVariant
    {
        QVariant v;
        switch (role)
        {
        case Qt::DisplayRole:
        case Qt::EditRole:
            v = cast(entity)->cantidad();
            break;
        default:
            v = QVariant();
        }
        return v;
    },
    [&] (EntityBasePtr entity, const QVariant& value, int role) ->bool
    {
        if (role == Qt::EditRole)
        {
            cast(entity)->setCantidad(value.toDouble());
            return true;
        }
        else
        {
            return false;
        }
    });

    //    setField(10, "Unidad de medida");
    setField(10, "Fecha Estimada Inicio",
             [&] (EntityBasePtr entity, int role) -> QVariant
    {
        QVariant v;
        switch (role)
        {
        case Qt::DisplayRole:
        case Qt::EditRole:
            v = cast(entity)->fechaEstimadaInicio();
            break;
        default:
            v = QVariant();
        }
        return v;
    },
    [&] (EntityBasePtr entity, const QVariant& value, int role) ->bool
    {
        if (role == Qt::EditRole)
        {
            QDateTime dt = value.toDateTime();
            cast(entity)->setFechaEstimadaInicio(dt);
            return true;
        }
        else
        {
            return false;
        }
    });

    setField(11, "Fecha Estimada de Finalización",
             [&] (EntityBasePtr entity, int role) -> QVariant
    {
        QVariant v;
        switch (role)
        {
        case Qt::DisplayRole:
        case Qt::EditRole:
            v = cast(entity)->fechaEstimadaFin();
            break;
        default:
            v = QVariant();
        }
        return v;
    },
    [&] (EntityBasePtr entity, const QVariant& value, int role) ->bool
    {
        if (role == Qt::EditRole)
        {
            QDateTime dt = value.toDateTime();
            cast(entity)->setFechaEstimadaFin(dt);
            return true;
        }
        else
        {
            return false;
        }
    });

    setField(12, "Duración",
             [&] (EntityBasePtr entity, int role) -> QVariant
    {
        QVariant v;
        switch (role)
        {
        case Qt::DisplayRole:
        case Qt::EditRole:
            v = cast(entity)->duracion();
            break;
        default:
            v = QVariant();
        }
        return v;
    });

    setField(13, "Costo",
             [&] (EntityBasePtr entity, int role) -> QVariant
    {
        QVariant v;
        switch (role)
        {
        case Qt::DisplayRole:
        case Qt::EditRole:
            v = cast(entity)->costo();
            break;
        default:
            v = QVariant();
        }
        return v;
    });

    setField(14, "Precio",
             [&] (EntityBasePtr entity, int role) -> QVariant
    {
        QVariant v;
        switch (role)
        {
        case Qt::DisplayRole:
        case Qt::EditRole:
            v = cast(entity)->precio();
            break;
        default:
            v = QVariant();
        }
        return v;
    });

    setField(15, "Avance",
             [&] (EntityBasePtr entity, int role) -> QVariant
    {
        QVariant v;
        switch (role)
        {
        case Qt::DisplayRole:
        case Qt::EditRole:
            v = cast(entity)->pctCompletado();
            break;
        default:
            v = QVariant();
        }
        return v;
    },
    [&] (EntityBasePtr entity, const QVariant& value, int role) ->bool
    {
        if (role == Qt::EditRole)
        {
            cast(entity)->setPctCompletado(value.toDouble());
            return true;
        }
        else
        {
            return false;
        }
    });

}

QVariant ExecutionTaskModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return ModelBase::headerData(section, orientation, role);
}

QVariant ExecutionTaskModel::modelData(EntityBasePtr entity, int column, int role) const
{
    ExecutionTaskPtr p = qSharedPointerDynamicCast<ExecutionTask>(entity);
    if (role == Qt::DisplayRole)
    {
        switch (column)
        {
        case 0:
        {
            return p->id();
            break;
        }
        case 1:
        {
            return p->idTareaPadre();
            break;
        }
        case 2:
        {
            return p->idMaterialTask();
            break;
        }
        case 3:
        {
            return p->idProveedor();
            break;
        }
        case 4:
        {
            if (p->idTareaPadre() != -1)
            {
                ExecutionTaskPtr tp = qSharedPointerDynamicCast<ExecutionTask>(p->tareaPadre());
                return tp->name();
            }
            else
            {
                return QVariant();
            }
            break;
        }
        case 5:
        {
            return p->name();
            break;
        }
        case 6:
        {
            if (p->idMaterialTask() != -1)
            {
                MaterialPtr m = qSharedPointerDynamicCast<Material>(p->materialTask());
                if (m->idRubro() != -1)
                {
                    RubroPtr r = qSharedPointerDynamicCast<Rubro>(m->rubro());
                    return r.isNull() ? QVariant() : r->name();
                }
                else
                {
                    return QVariant();
                }
            }
            else
            {
                return QVariant();
            }
            break;
        }
        case 7:
        {
            if (p->idMaterialTask() != -1)
            {
                MaterialPtr m = qSharedPointerDynamicCast<Material>(p->materialTask());
                return m->name();
            }
            else
            {
                return QVariant();
            }
            break;
        }
        case 8:
        {
            if (p->idProveedor() != -1)
            {
                ProveedorPtr prov = qSharedPointerDynamicCast<Proveedor>(p->proveedor());
                return prov->name();
            }
            else
            {
                return QVariant();
            }
            break;
        }
        case 9:
        {
            if (Qt::DisplayRole)
            {
                return p->cantidadToString();
            }
            else
            {
                return p->cantidad();
            }
            break;
        }
        case 10:
        {
            return p->fechaEstimadaInicio();
            break;
        }
        case 11:
        {
            return p->fechaEstimadaFin();
            break;
        }
        case 12:
        {
            return p->duracion();
            break;
        }
        case 13:
        {
            return p->costo();
            break;
        }
        case 14:
        {
            return p->precio();
            break;
        }
        case 15:
        {
            return p->pctCompletado();
            break;
        }
        default:
            return QVariant();
            break;
        }
    }
    else if (column == columnCount())
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
    return QVariant();
}

bool ExecutionTaskModel::modelSetData(EntityBasePtr entity, int column, const QVariant &value, int)
{
    ExecutionTaskPtr p = qSharedPointerDynamicCast<ExecutionTask>(entity);
    bool result = false;
    switch (column)
    {
    case 0:
        result = true;
        break;
    case 1:
    {
        p->setIdTareaPadre(value.toInt());
        result = true;
        break;
    }
    case 2:
    {
        p->setIdMaterialTask(value.toInt());
        result = true;
        break;
    }
    case 3:
    {
        p->setIdProveedor(value.toInt());
        result = true;
        break;
    }
    case 4:
    {
        break;
    }
    case 5:
    {
        p->setName(value.toString());
        result = true;
        break;
    }
    case 6:
    {
        break;
        break;
    }
    case 7:
    {
        break;
    }
    case 8:
    {
        break;
    }
    case 9:
    {
        p->setCantidad(value.toDouble());
        result = true;
        break;
    }
    case 10:
        break;
    case 11:
    {
        QDateTime date = value.toDateTime();
        p->setFechaEstimadaInicio(date);
        result = true;
        break;
    }
    case 12:
    {
        QDateTime date = value.toDateTime();
        p->setFechaEstimadaFin(date);
        result = true;
        break;
    }
    case 13:
    {
        break;
    }
    case 14:
    {
        break;
    }
    case 15:
    {
        break;
    }
    case 16:
    {
        p->setPctCompletado(value.toDouble());
        break;
    }
    default:
        break;
    }
    return result;
}

QString ExecutionTaskModel::_getSQLRead() const
{
    return "select * from tareasEjecucion;";
}

int ExecutionTaskModel::_loadEntity(QSqlRecord record)
{
    int id = record.value(record.indexOf("id")).toInt();

    int idTareaPadre = record.value(record.indexOf("idTareaPadre")).toInt();
    QString name = record.value(record.indexOf("name")).toString();
    int idMaterialTask = record.value(record.indexOf("idMaterialTask")).toInt();
    int idProveedor = record.value(record.indexOf("idProveedor")).toInt();
    double cantidad = record.value(record.indexOf("cantidad")).toDouble();
    QDateTime fechaEstimadaInicio = record.value(record.indexOf("fechaEstimadaInicio")).toDateTime();
    QDateTime fechaEstimadaFin = record.value(record.indexOf("fechaEstimadaFin")).toDateTime();
    KDGantt::ItemType taskType = static_cast<KDGantt::ItemType>(record.value(record.indexOf("taskType")).toInt());
    int idTareaPlanificada = record.value(record.indexOf("idTareaPlanificada")).toInt();
    double pctAvance = record.value(record.indexOf("pctAvance")).toDouble();
    QDateTime fechaRealInicio = record.value(record.indexOf("fecharealInicio")).toDateTime();
    QDateTime fechaRealFin = record.value(record.indexOf("fechaRealFin")).toDateTime();
    bool isSplittedTask = record.value(record.indexOf("isSplitted")).toBool();


    EntityBasePtr entity = ExecutionTaskPtr::create(id, idTareaPadre,
                                                    name, idMaterialTask, idProveedor,
                                                    cantidad, fechaEstimadaInicio, fechaEstimadaFin,
                                                    taskType, idTareaPlanificada,
                                                    pctAvance, fechaRealInicio, fechaRealFin, isSplittedTask);

    qSharedPointerDynamicCast<ExecutionTask>(entity)->setIdProyecto(_idProyecto);
    addEntity(entity);
    return id;
}

EntityBasePtr ExecutionTaskModel::internalCreateEntity(int assignedId)
{
    ExecutionTaskPtr p = ExecutionTaskPtr::create(assignedId);
    p->setIdProyecto(_idProyecto);
    return p;
}


void ExecutionTaskModel::editEntity(int row)
{
    EntityBasePtr entity = getItemByRowid(row);
    DlgEditExecutionTask dlg(this, entity);
    dlg.exec();
}

EntityBasePtr ExecutionTaskModel::createEntity()
{
    EntityBasePtr entity = ModelBase::createEntity();
    qSharedPointerDynamicCast<ExecutionTask>(entity)->setIdProyecto(_idProyecto);
    return entity;
}

int ExecutionTaskModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
    {
        return static_cast<Node*>(parent.internalPointer())->childCount();
    }
    else
    {
        return _root->childCount();
    }
}

QModelIndex ExecutionTaskModel::index(int row, int column, const QModelIndex &parent) const
{
    Node* p = parent.isValid() ? static_cast<Node*>(parent.internalPointer()) : _root;

    if (row < 0 || row >= p->childCount())
    {
        return QModelIndex();
    }
    else
    {
        return ModelBase::createIndex(row, column, p->child(row));
    }
}

QModelIndex ExecutionTaskModel::parent(const QModelIndex &child) const
{
    if (!child.isValid())
        return QModelIndex();

    Node* n = static_cast<Node*>(child.internalPointer());
    assert(n);

    Node* p = n->parent();

    if (p == _root)
        return QModelIndex();

    Node* pp = p->parent();
    assert(pp);
    return ModelBase::createIndex(pp->childNumber(p), 0, p);
}

QList<EntityBasePtr> ExecutionTaskModel::tasks() const
{
    return entities();
}

QVariant ExecutionTaskModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    ExecutionTaskModel::Node *n = static_cast<ExecutionTaskModel::Node*>(index.internalPointer());
    assert(n);
    return modelData(n->entity(), index.column(), role);
}

bool ExecutionTaskModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
        return false;
    qDebug() << "ProjectModel::setData" << index.column() << role << value;

    Node* n = static_cast<Node*>(index.internalPointer());
    assert(n);

    bool result = modelSetData(n->entity(), index.column(), value, role);
    emit dataChanged(index, index);
    return result;
}

void ExecutionTaskModel::postProcessData()
{
    QList<EntityBasePtr> ents = _entities.values();
    foreach (EntityBasePtr entity, ents)
    {
        ExecutionTaskPtr p = qSharedPointerDynamicCast<ExecutionTask>(entity);
        _root->createChild(p);
    }
}

bool ExecutionTaskModel::insertRows(int row, int count, const QModelIndex& parent)
{
    beginInsertRows( parent, row, row+count-1 );
    bool res = ModelBase::insertRows(row, count, parent);
    EntityBasePtr entity = getItemByRowid(row);
    if (res)
    {
        Node* p = _root;
        if (parent.isValid())
            p = static_cast<Node*>(parent.internalPointer());

        assert( p );

        for ( int i = 0; i < count; ++i )
        {
            Node* n = new Node(entity);
            p->insertChild(row+i, n);
        }
    }
    endInsertRows();
    return true;
}

void ExecutionTaskModel::editEntity(EntityBasePtr)
{
    /*DlgEditPlanningTask dlg(this, entity);
    dlg.exec();*/
}

int ExecutionTaskModel::idProyecto() const
{
    return _idProyecto;
}

void ExecutionTaskModel::cloneFromPlanning()
{
    IModel *model = GlobalContainer::instance().projectLibrary(_idProyecto)->model(Tables::PlanningTasks);
    PlanningTaskModel* planModel = dynamic_cast<PlanningTaskModel*>(model);
    QList<int> ids = planModel->ids().toList();
    //beginInsertRows(QModelIndex(), 0, ids.count());
    std::sort(ids.begin(), ids.end());
    foreach (int id, ids)
    {
        EntityBasePtr entity = createEntity();
        ExecutionTaskPtr execTask = qSharedPointerDynamicCast<ExecutionTask>(entity);
        entity = planModel->getItem(id);
        execTask->setPlanningTask(entity, true);
    }
    //endInsertRows();
    calculateParentsBasedOnPlanningParents();
    postProcessData();
    emit dataChanged(QModelIndex(), QModelIndex());
}

int ExecutionTaskModel::idFromPlanning(int idPlanningTask)
{
    if (idPlanningTask != -1)
    {
        foreach (int key, ids())
        {
            ExecutionTaskPtr et = qSharedPointerDynamicCast<ExecutionTask>(getItem(key));
            if (et->idPlanningTask() == idPlanningTask)
            {
                return et->id();
            }
        }
    }
    return -1;
}

void ExecutionTaskModel::calculateParentsBasedOnPlanningParents()
{
    QSet<int> keys = ids();
    foreach (int key, keys)
    {
        ExecutionTaskPtr et = qSharedPointerDynamicCast<ExecutionTask>(getItem(key));
        PlanningTaskPtr pt = qSharedPointerDynamicCast<PlanningTask>(et->planningTask());
        int idPlanningTaskPadre = pt->idTareaPadre();
        int idExecTaskPadre = idFromPlanning(idPlanningTaskPadre);
        et->setIdTareaPadre(idExecTaskPadre);
    }
}

ExecutionTaskPtr ExecutionTaskModel::cast(EntityBasePtr entity)
{
    return qSharedPointerDynamicCast<ExecutionTask>(entity);
}
