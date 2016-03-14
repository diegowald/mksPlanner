#include "planningtaskmodelconstraintfiltered.h"
#include <QSet>
#include "models/planningtaskconstraint.h"
#include "globalcontainer.h"
#include "models/planningtask.h"

PlanningTaskModelConstraintFiltered::PlanningTaskModelConstraintFiltered(int idProyecto, int idTask, PlanningTaskModelConstraint *model, QObject *parent) : ModelBase(Tables::PlanningTasksConstraints, "", false, "", parent)
{
    _idProyecto = idProyecto;
    _idTask = idTask;
    _model = model;
    setField(1, "idTask1",
             [&] (EntityBasePtr, int) -> QVariant
    {
        return QVariant();
    },
    [&] (EntityBasePtr, const QVariant&, int) -> bool
    {
        return false;
    });

    setField(2, "idTask2",
             [&] (EntityBasePtr, int) -> QVariant
    {
        return QVariant();
    },
    [&] (EntityBasePtr, const QVariant&, int) -> bool
    {
        return false;
    });

    setField(3, "Type",
             [&] (EntityBasePtr, int) -> QVariant
    {
        return QVariant();
    },
    [&] (EntityBasePtr, const QVariant&, int) -> bool
    {
        return false;
    });

    setField(4, "RelationType",
             [&] (EntityBasePtr, int) -> QVariant
    {
        return QVariant();
    },
    [&] (EntityBasePtr, const QVariant&, int) -> bool
    {
        return false;
    });

    setField(5, "Restricción",
             [&idProyecto] (EntityBasePtr, int) -> QVariant
    {
        return QVariant();
    },
    [&] (EntityBasePtr, const QVariant&, int) -> bool
    {
        return false;
    });

    extractIds();
}


void PlanningTaskModelConstraintFiltered::extractIds()
{
    QList<int> idsToProcess = _model->ids().toList();
    foreach (int id, idsToProcess)
    {
        PlanningTaskConstraintPtr pt = qSharedPointerDynamicCast<PlanningTaskConstraint>(_model->getItem(id));
        if (pt->idTask1() == _idTask)
        {
            _ids.append(id);
        }
    }
}

int PlanningTaskModelConstraintFiltered::rowCount(const QModelIndex &) const
{
    return _ids.count();
}

QVariant PlanningTaskModelConstraintFiltered::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    QVariant res;
    if (role == Qt::DisplayRole)
    {
        int id = _ids.at(index.row());
        EntityBasePtr entity = _model->getItem(id);
        PlanningTaskConstraintPtr pt =
                qSharedPointerDynamicCast<PlanningTaskConstraint>(entity);

        switch (index.column())
        {
        case 1:
            res = pt->idTask1();
            break;
        case 2:
            res = pt->idTask2();
            break;
        case 3:
            res = pt->Type();
            break;
        case 4:
            res = pt->RelationType();
            break;
        case 5:
        {

            if ((pt->idTask1() != -1) && (pt->idTask2() != -1))
            {
                QString s;
                switch (pt->RelationType())
                {
                case 0:
                    s = "Termina %1 y comienza %2";
                    break;
                case 1:
                    s = "Termina %1 y Termina %2";
                    break;
                case 2:
                    s = "Comienza %1 y Comienza %2";
                    break;
                case 3:
                    s = "Comienza %1 y Termina %2";
                    break;
                default:
                    break;
                }
                QString tipo;
                switch (pt->Type())
                {
                case 0:
                    tipo = "Soft";
                    break;
                case 1:
                    tipo = "Hard";
                    break;
                default:
                    tipo = "";
                    break;
                }

                EntityBasePtr et1 = GlobalContainer::instance().projectLibrary(_idProyecto)->model(Tables::PlanningTasks)->getItem(pt->idTask1());
                PlanningTaskPtr pt1 = qSharedPointerDynamicCast<PlanningTask>(et1);
                res = pt1->name();
                EntityBasePtr et2 = GlobalContainer::instance().projectLibrary(_idProyecto)->model(Tables::PlanningTasks)->getItem(pt->idTask2());
                PlanningTaskPtr pt2 = qSharedPointerDynamicCast<PlanningTask>(et2);

                if (!s.isEmpty() && !tipo.isEmpty())
                    s += " - %3";
                return s.arg(pt1->name()).arg(pt2->name()).arg(tipo);
            }
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
        default:
            res = QVariant();
            break;
        }
    }
    return res;
}


EntityBasePtr PlanningTaskModelConstraintFiltered::getItemByRowid(int row)
{
    int id = _ids.at(row);
    return _model->getItem(id);
}

EntityBasePtr PlanningTaskModelConstraintFiltered::internalCreateEntity(int)
{
    int rowCount = _model->rowCount();
    QModelIndex index;

    /*if (!*/_model->insertRow(rowCount, index.parent());
    /*return;*/

    EntityBasePtr entity = _model->getItemByRowid(rowCount);
    qSharedPointerDynamicCast<PlanningTaskConstraint>(entity)->setIdTask1(_idTask);
    _ids.append(entity->id());

    _model->editEntity(rowCount);
    return entity;
}
/*
QVariant PlanningTaskModelConstraintFiltered::data(const QModelIndex &index, int role) const
{
    int id = _ids.at(index.row());
    return ModelBase::data(id, index.column(), role);
}*/


QString PlanningTaskModelConstraintFiltered::_getSQLRead() const
{
    return "";
}

int PlanningTaskModelConstraintFiltered::_loadEntity(QSqlRecord)
{
    return -1;
}

void PlanningTaskModelConstraintFiltered::editEntity(int)
{
}

QVariant PlanningTaskModelConstraintFiltered::modelData(EntityBasePtr, int, int) const
{
    return QVariant();
}

bool PlanningTaskModelConstraintFiltered::modelSetData(EntityBasePtr, int, const QVariant &, int)
{
    return true;
}

bool PlanningTaskModelConstraintFiltered::removeRow(int row, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row);
    int id = _ids.at(row);
    _model->removeById(id);
    _ids.removeAt(row);
    endRemoveRows();
    return true;
}

PlanningTaskConstraintPtr PlanningTaskModelConstraintFiltered::cast(EntityBasePtr entity)
{
    return qSharedPointerDynamicCast<PlanningTaskConstraint>(entity);
}
