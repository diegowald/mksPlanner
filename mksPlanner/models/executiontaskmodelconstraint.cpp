#include "executiontaskmodelconstraint.h"
//#include "views/dlgeditplanningtaskconstraint.h"
#include "models/planningtaskmodelconstraint.h"
#include "models/executiontaskconstraint.h"
#include "globalcontainer.h"


ExecutionTaskModelConstraint::ExecutionTaskModelConstraint(int idProyecto, QObject *parent) :
    ModelBase(Tables::PlanningTasksConstraints, "executionConstraints", false, "proyectos", parent)

{
    _idProyecto = idProyecto;
    defineColumnNames();
}


QString ExecutionTaskModelConstraint::_getSQLRead() const
{
    return "SELECT * FROM tareasEjecucionConstraints;";
}

int ExecutionTaskModelConstraint::_loadEntity(QSqlRecord record)
{
    int id = record.value(record.indexOf("id")).toInt();
    int idTask1 = record.value(record.indexOf("idTask1")).toInt();
    int idTask2 = record.value(record.indexOf("idTask2")).toInt();
    int type = record.value(record.indexOf("type")).toInt();
    int relationType = record.value(record.indexOf("relationType")).toInt();
    int idPlanningTask = record.value(record.indexOf("idPlanningConstraint")).toInt();
    EntityBasePtr entity = ExecutionTaskConstraintPtr::create(id, idTask1, idTask2, type, relationType, idPlanningTask);
    addEntity(entity);
    return id;
}

void ExecutionTaskModelConstraint::editEntity(int row)
{
    EntityBasePtr entity = getItemByRowid(row);
    ExecutionTaskConstraintPtr pt = qSharedPointerDynamicCast<ExecutionTaskConstraint>(entity);

/*    DlgEditPlanningTaskConstraint dlg(pt, _idProyecto);
    if (dlg.exec() == QDialog::Accepted)
        emit dataChanged(QModelIndex(), QModelIndex());*/
}


EntityBasePtr ExecutionTaskModelConstraint::internalCreateEntity(int assignedId)
{
    ExecutionTaskConstraintPtr pt = ExecutionTaskConstraintPtr::create(assignedId);
    return pt;
}

QVariant ExecutionTaskModelConstraint::modelData(EntityBasePtr entity, int column, int role) const
{
    ExecutionTaskConstraintPtr pt = qSharedPointerDynamicCast<ExecutionTaskConstraint>(entity);
    QVariant res;
    switch (column)
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

    default:
        res = QVariant();
        break;
    }
}

bool ExecutionTaskModelConstraint::modelSetData(EntityBasePtr entity, int column, const QVariant &value, int role)
{
}

void ExecutionTaskModelConstraint::postProcessData()
{
    emit refreshed();
}

void ExecutionTaskModelConstraint::defineColumnNames()
{
    setField(1, "idTask1");
    setField(2, "idTask2");
    setField(3, "Type");
    setField(4, "RelationType");
}

void ExecutionTaskModelConstraint::cloneFromPlanning()
{
    ModelBase *model = GlobalContainer::instance().projectLibrary(_idProyecto)->model(Tables::PlanningTasksConstraints);
    PlanningTaskModelConstraint* planModel = dynamic_cast<PlanningTaskModelConstraint*>(model);
    QSet<int> ids = planModel->ids();
    //beginInsertRows(QModelIndex(), 0, ids.count());
    foreach (int id, ids)
    {
        EntityBasePtr entity = createEntity();
        ExecutionTaskConstraintPtr execTask = qSharedPointerDynamicCast<ExecutionTaskConstraint>(entity);
        entity = planModel->getItem(id);
        execTask->setPlanningTaskConstraint(entity, true);
    }
    //endInsertRows();
    postProcessData();
}
