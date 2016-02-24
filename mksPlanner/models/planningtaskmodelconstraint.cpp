#include "planningtaskmodelconstraint.h"
#include "models/planningtaskconstraint.h"
#include "views/dlgeditplanningtaskconstraint.h"


PlanningTaskModelConstraint::PlanningTaskModelConstraint(int idProyecto, QObject *parent) :
    ModelBase(Tables::PlanningTasksConstraints, "tasksConstraints", false, "proyectos", parent)

{
    _idProyecto = idProyecto;
    defineColumnNames();
}


QString PlanningTaskModelConstraint::_getSQLRead() const
{
    return "SELECT * FROM tareasPlanificadasConstraints;";
}

int PlanningTaskModelConstraint::_loadEntity(QSqlRecord record)
{
    int id = record.value(record.indexOf("id")).toInt();
    int idTask1 = record.value(record.indexOf(":idTask1")).toInt();
    int idTask2 = record.value(record.indexOf(":idTask2")).toInt();
    int type = record.value(record.indexOf(":type")).toInt();
    int relationType = record.value(record.indexOf(":relationType")).toInt();
    EntityBasePtr entity = PlanningTaskConstraintPtr::create(id, idTask1, idTask2, type, relationType);
    addEntity(entity);
    return id;
}

void PlanningTaskModelConstraint::editEntity(int row)
{
    EntityBasePtr entity = getItemByRowid(row);
    PlanningTaskConstraintPtr pt = qSharedPointerDynamicCast<PlanningTaskConstraint>(entity);

    DlgEditPlanningTaskConstraint dlg(pt, _idProyecto);
    if (dlg.exec() == QDialog::Accepted)
        emit dataChanged(QModelIndex(), QModelIndex());
}


EntityBasePtr PlanningTaskModelConstraint::internalCreateEntity(int assignedId)
{
    PlanningTaskConstraintPtr pt = PlanningTaskConstraintPtr::create(assignedId);
    return pt;
}

QVariant PlanningTaskModelConstraint::modelData(EntityBasePtr entity, int column, int role) const
{
    PlanningTaskConstraintPtr pt = qSharedPointerDynamicCast<PlanningTaskConstraint>(entity);
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

bool PlanningTaskModelConstraint::modelSetData(EntityBasePtr entity, int column, const QVariant &value, int role)
{
}

void PlanningTaskModelConstraint::postProcessData()
{
}

void PlanningTaskModelConstraint::defineColumnNames()
{
    setField(1, "idTask1");
    setField(2, "idTask2");
    setField(3, "Type");
    setField(4, "RelationType");
}
