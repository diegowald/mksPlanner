#include "planningtaskmodel.h"
#include <QSharedPointer>
#include <QDate>
#include "models/planningtask.h"
#include "models/material.h"
#include "models/rubro.h"
#include "models/proveedor.h"
#include "views/dlgeditplanningtask.h"
#include <KDGantt>
#include <models/unit.h>
#include "globalcontainer.h"
#include <cassert>
#include <QMap>
/* NODE */

PlanningTaskModel::Node::Node(EntityBasePtr entity, Node *parent)
{
    _parent = parent;
    _entity = entity;
    _id = (_entity.isNull()) ? -1 : _entity->id();
    if (_parent)
    {
        _parent->addChild(this);
    }
}

void PlanningTaskModel::Node::addChild(Node *node)
{
    node->setParent(this);
    _children.append(node);
}

PlanningTaskModel::Node::~Node()
{
    while (!_children.isEmpty())
    {
        PlanningTaskModel::Node *node = _children.front();
        delete node;
        _children.pop_front();
    }
    //if (_parent) _parent->removeChild(this);
}

void PlanningTaskModel::Node::insertChild( int i, Node* node)
{
    node->setParent(this);
    _children.insert(i, node);
}

bool PlanningTaskModel::Node::createChild(EntityBasePtr entity)
{
    PlanningTaskPtr p = qSharedPointerDynamicCast<PlanningTask>(entity);
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

void PlanningTaskModel::Node::removeChild( Node* node)
{
    /*    _children.removeAt(_children.indexOf(node));

    node->setParent(0);
    node->_children.removeAll(node);*/
    if (!node->entity().isNull())
        node->_entity->deleteEntity();
    _children.removeOne(node);
    delete node;
}

PlanningTaskModel::Node* PlanningTaskModel::Node::parent() const
{
    return _parent;
}

void PlanningTaskModel::Node::setParent(Node *parent)
{
    _parent = parent;
}

int PlanningTaskModel::Node::childCount() const
{
    return _children.count();
}

int PlanningTaskModel::Node::childNumber(Node* n) const
{
    return _children.indexOf(n);
}

PlanningTaskModel::Node* PlanningTaskModel::Node::child(int i) const
{
    return _children.at(i);
}

EntityBasePtr PlanningTaskModel::Node::entity() const
{
    return _entity;
}



/* /NODE */

PlanningTaskModel::PlanningTaskModel(int idProyecto, QObject *parent)
    : ModelBase(Tables::PlanningTasks, "planningtasks", false, "proyectos", parent)
{
    _idProyecto = idProyecto;
    defineColumnNames();
    addDependency(static_cast<int>(Tables::Tareas));
    addDependency(static_cast<int>(Tables::Rubros));
    addDependency(static_cast<int>(Tables::Unidades));
    addDependency(static_cast<int>(Tables::Proveedores));
    _root = new Node(EntityBasePtr(), NULL);
}

void PlanningTaskModel::defineColumnNames()
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
            break;
        }
        return v;
    },
    [&] (EntityBasePtr entity, const QVariant& value, int role) -> bool
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
            break;
        }
        return v;
    },
    [&] (EntityBasePtr entity, const QVariant& value, int role) -> bool
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
            break;
        }
        return v;
    },
    [&] (EntityBasePtr entity, const QVariant& value, int role) -> bool
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
                v = qSharedPointerDynamicCast<Material>(cast(entity)->tareaPadre())->name();
            }
            else
            {
                v = QVariant();
            }
            break;
        default:
            v = QVariant();
            break;
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
            break;
        }
        return v;
    },
    [&] (EntityBasePtr entity, const QVariant& value, int role) -> bool
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
                MaterialPtr m = qSharedPointerDynamicCast<Material>(cast(entity)->materialTask());
                if (m->idRubro() != -1)
                {
                    RubroPtr r = qSharedPointerDynamicCast<Rubro>(m->rubro());
                    v = r.isNull() ? QVariant() : r->name();
                }
                else
                {
                    v = QVariant();
                }
            }
            break;
        default:
            v = QVariant();
            break;
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
                MaterialPtr m = qSharedPointerDynamicCast<Material>(cast(entity)->materialTask());
                v = m->name();
            }
            else
            {
                v = QVariant();
            }
            break;
        default:
            v = QVariant();
            break;
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
                ProveedorPtr prov = qSharedPointerDynamicCast<Proveedor>(cast(entity)->proveedor());
                v = prov->name();
            }
            else
            {
                v = QVariant();
            }
            break;
        default:
            v = QVariant();
            break;
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
            break;
        }
        return v;
    },
    [&] (EntityBasePtr entity, const QVariant& value, int role) -> bool
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

    setField(10, "Unidad de medida",
             [&] (EntityBasePtr entity, int role) -> QVariant
    {
        QVariant v;
        switch (role)
        {
        case Qt::DisplayRole:
        case Qt::EditRole:
            if (cast(entity)->idMaterialTask() != -1)
            {
                MaterialPtr m = qSharedPointerDynamicCast<Material>(cast(entity)->materialTask());
                if (m->idUnit() != -1)
                {
                    UnitPtr unit = qSharedPointerDynamicCast<Unit>(m->unit());
                    v = unit->name();
                }
                else
                {
                    v = QVariant();
                }
            }
            else
            {
                v = QVariant();
            }
            break;
        default:
            v = QVariant();
            break;
        }
        return v;
    });

    setField(11, "Fecha Estimada Inicio",
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
            break;
        }
        return v;
    },
    [&] (EntityBasePtr entity, const QVariant& value, int role) -> bool
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

    setField(12, "Fecha Estimada de Finalización",
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
            break;
        }
        return v;
    },
    [&] (EntityBasePtr entity, const QVariant& value, int role) -> bool
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

    setField(13, "Duración",
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
            break;
        }
        return v;
    });

    setField(14, "Costo",
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
            break;
        }
        return v;
    });

    setField(15, "Precio",
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
            break;
        }
        return v;
    });
}

QVariant PlanningTaskModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return ModelBase::headerData(section, orientation, role);
}

QVariant PlanningTaskModel::modelData(EntityBasePtr entity, int column, int role) const
{
    PlanningTaskPtr p = qSharedPointerDynamicCast<PlanningTask>(entity);
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
                PlanningTaskPtr tp = qSharedPointerDynamicCast<PlanningTask>(p->tareaPadre());
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
            return p->cantidad();
            break;
        }
        case 10:
        {
            if (p->idMaterialTask() != -1)
            {
                MaterialPtr m = qSharedPointerDynamicCast<Material>(p->materialTask());
                if (m->idUnit() != -1)
                {
                    UnitPtr unit = qSharedPointerDynamicCast<Unit>(m->unit());
                    return unit->name();
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
        case 11:
        {
            return p->fechaEstimadaInicio();
            break;
        }
        case 12:
        {
            return p->fechaEstimadaFin();
            break;
        }
        case 13:
        {
            return p->duracion();
            break;
        }
        case 14:
        {
            return p->costo();
            break;
        }
        case 15:
        {
            return p->precio();
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

bool PlanningTaskModel::modelSetData(EntityBasePtr entity, int column, const QVariant &value, int)
{
    PlanningTaskPtr p = qSharedPointerDynamicCast<PlanningTask>(entity);
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
    default:
        break;
    }
    return result;
}

QString PlanningTaskModel::_getSQLRead() const
{
    return "select * from tareasPlanificadas;";
}

int PlanningTaskModel::_loadEntity(QSqlRecord record)
{
    int id = record.value(record.indexOf("id")).toInt();

    int idTareaPadre = record.value(record.indexOf("idTareaPadre")) .toInt();
    QString name = record.value(record.indexOf("name")).toString();
    int idMaterialTask = record.value(record.indexOf("idMaterialTask")).toInt();
    int idProveedor = record.value(record.indexOf("idProveedor")).toInt();
    double cantidad = record.value(record.indexOf("cantidad")).toDouble();
    QDateTime fechaEstimadaInicio = record.value(record.indexOf("fechaEstimadaInicio")).toDateTime();
    QDateTime fechaEstimadaFin = record.value(record.indexOf("fechaEstimadaFin")).toDateTime();
    KDGantt::ItemType taskType = static_cast<KDGantt::ItemType>(record.value(record.indexOf("taskType")).toInt());

    EntityBasePtr entity = PlanningTaskPtr::create(id, idTareaPadre,
                                                   name, idMaterialTask, idProveedor,
                                                   cantidad, fechaEstimadaInicio, fechaEstimadaFin,
                                                   taskType);
    qSharedPointerDynamicCast<PlanningTask>(entity)->setIdProyecto(_idProyecto);
    addEntity(entity);
    return id;
}

EntityBasePtr PlanningTaskModel::internalCreateEntity(int assignedId)
{
    PlanningTaskPtr p = PlanningTaskPtr::create(assignedId);
    p->setIdProyecto(_idProyecto);
    return p;
}


void PlanningTaskModel::editEntity(int row)
{
    EntityBasePtr entity = getItemByRowid(row);
    DlgEditPlanningTask dlg(this, entity);
    dlg.exec();
}

EntityBasePtr PlanningTaskModel::createEntity()
{
    EntityBasePtr entity = ModelBase::createEntity();
    qSharedPointerDynamicCast<PlanningTask>(entity)->setIdProyecto(_idProyecto);
    return entity;
}

int PlanningTaskModel::rowCount(const QModelIndex &parent) const
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

QModelIndex PlanningTaskModel::index(int row, int column, const QModelIndex &parent) const
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

QModelIndex PlanningTaskModel::parent(const QModelIndex &child) const
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

QList<EntityBasePtr> PlanningTaskModel::tasks() const
{
    return entities();
}

QVariant PlanningTaskModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    PlanningTaskModel::Node *n = static_cast<PlanningTaskModel::Node*>(index.internalPointer());
    assert(n);
    return modelData(n->entity(), index.column(), role);
}

bool PlanningTaskModel::setData(const QModelIndex &index, const QVariant &value, int role)
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

void PlanningTaskModel::postProcessData()
{
    QList<EntityBasePtr> ents = _entities.values();
    foreach (EntityBasePtr entity, ents)
    {
        PlanningTaskPtr p = qSharedPointerDynamicCast<PlanningTask>(entity);
        _root->createChild(p);
    }
}

bool PlanningTaskModel::insertRows(int row, int count, const QModelIndex& parent)
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

void PlanningTaskModel::editEntity(EntityBasePtr entity)
{
    DlgEditPlanningTask dlg(this, entity);
    dlg.exec();
}

int PlanningTaskModel::idProyecto() const
{
    return _idProyecto;
}

PlanningTaskPtr PlanningTaskModel::cast(EntityBasePtr entity)
{
    return qSharedPointerDynamicCast<PlanningTask>(entity);
}
