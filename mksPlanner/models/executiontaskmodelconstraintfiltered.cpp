#include "executiontaskmodelconstraintfiltered.h"
#include <QSet>
#include "models/executiontaskconstraint.h"
#include "globalcontainer.h"
#include "models/executiontask.h"

ExecutionTaskModelConstraintFiltered::ExecutionTaskModelConstraintFiltered(int idProyecto, int idTask, ExecutionTaskModelConstraint *model, QObject *parent) : ModelBase(Tables::ExecutionTasksConstraints, "", false, "", parent)
{
    _idProyecto = idProyecto;
    _idTask = idTask;
    _model = model;
    setField(1, "idTask1");
    setField(2, "idTask2");
    setField(3, "Type");
    setField(4, "RelationType");
    setField(5, "Restricción");
    extractIds();
}


void ExecutionTaskModelConstraintFiltered::extractIds()
{
    QList<int> idsToProcess = _model->ids().toList();
    foreach (int id, idsToProcess)
    {
        ExecutionTaskConstraintPtr pt = qSharedPointerDynamicCast<ExecutionTaskConstraint>(_model->getItem(id));
        if (pt->idTask1() == _idTask)
        {
            _ids.append(id);
        }
    }
}

int ExecutionTaskModelConstraintFiltered::rowCount(const QModelIndex &parent) const
{
    return _ids.count();
}

QVariant ExecutionTaskModelConstraintFiltered::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    QVariant res;
    if (role == Qt::DisplayRole)
    {
        int id = _ids.at(index.row());
        EntityBasePtr entity = _model->getItem(id);
        ExecutionTaskConstraintPtr pt =
                qSharedPointerDynamicCast<ExecutionTaskConstraint>(entity);

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

                EntityBasePtr et1 = GlobalContainer::instance().projectLibrary(_idProyecto)->model(Tables::ExecutionTasks)->getItem(pt->idTask1());
                ExecutionTaskPtr pt1 = qSharedPointerDynamicCast<ExecutionTask>(et1);
                res = pt1->name();
                EntityBasePtr et2 = GlobalContainer::instance().projectLibrary(_idProyecto)->model(Tables::ExecutionTasks)->getItem(pt->idTask2());
                ExecutionTaskPtr pt2 = qSharedPointerDynamicCast<ExecutionTask>(et2);

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


EntityBasePtr ExecutionTaskModelConstraintFiltered::getItemByRowid(int row)
{
    int id = _ids.at(row);
    return _model->getItem(id);
}

EntityBasePtr ExecutionTaskModelConstraintFiltered::internalCreateEntity(int assignedId)
{
    int rowCount = _model->rowCount();
    QModelIndex index;

    /*if (!*/_model->insertRow(rowCount, index.parent());
    /*return;*/

    EntityBasePtr entity = _model->getItemByRowid(rowCount);
    qSharedPointerDynamicCast<ExecutionTaskConstraint>(entity)->setIdTask1(_idTask);
    _ids.append(entity->id());

    _model->editEntity(rowCount);
    return entity;
}
/*
QVariant ExecutionTaskModelConstraintFiltered::data(const QModelIndex &index, int role) const
{
    int id = _ids.at(index.row());
    return ModelBase::data(id, index.column(), role);
}*/


QString ExecutionTaskModelConstraintFiltered::_getSQLRead() const
{
}

int ExecutionTaskModelConstraintFiltered::_loadEntity(QSqlRecord record)
{
}

void ExecutionTaskModelConstraintFiltered::editEntity(int row)
{
}

QVariant ExecutionTaskModelConstraintFiltered::modelData(EntityBasePtr entity, int column, int role) const
{
    return QVariant();
}

bool ExecutionTaskModelConstraintFiltered::modelSetData(EntityBasePtr entity, int column, const QVariant &value, int role)
{
}
