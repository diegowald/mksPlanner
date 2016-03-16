#include "executiontaskconstraint.h"
#include <QSqlQuery>
#include <QVariant>
#include "models/planningtaskconstraint.h"


ExecutionTaskConstraint::ExecutionTaskConstraint(int id) : EntityBase(id, true)
{
    _idTask1 = -1;
    _idTask2 = -1;
    _Type = -1;
    _RelationType = -1;
    _idPlanningConstraint = -1;
}

ExecutionTaskConstraint::ExecutionTaskConstraint(int id, int idTask1, int idTask2, int Type, int RelationType, int idPlanningTaskConstraint) : EntityBase(id)
{
    _idTask1 = idTask1;
    _idTask2 = idTask2;
    _Type = Type;
    _RelationType = RelationType;
    _idPlanningConstraint = idPlanningTaskConstraint;
}

int ExecutionTaskConstraint::idTask1() const
{
    return _idTask1;
}

int ExecutionTaskConstraint::idTask2() const
{
    return _idTask2;
}

int ExecutionTaskConstraint::Type() const
{
    return _Type;
}

int ExecutionTaskConstraint::RelationType() const
{
    return _RelationType;
}

void ExecutionTaskConstraint::setIdTask1(int value)
{
    _idTask1 = value;
    updateStatus();
}

void ExecutionTaskConstraint::setIdTask2(int value)
{
    _idTask2 = value;
    updateStatus();
}

void ExecutionTaskConstraint::setType(int value)
{
    _Type = value;
    updateStatus();
}

void ExecutionTaskConstraint::setRelationType(int value)
{
    _RelationType = value;
    updateStatus();
}

QString ExecutionTaskConstraint::toDebugString()
{
    return QString("De %1 a %2. Tipo %3. Relation Type: %4").arg(_idTask1)
            .arg(_idTask2).arg(_Type).arg(_RelationType);
}


QSqlQuery* ExecutionTaskConstraint::getQuery(QSqlDatabase &database)
{
    QSqlQuery *query = NULL;
    switch (status())
    {
    case EntityStatus::added:
    {
        query = new QSqlQuery(database);
        query->prepare("INSERT INTO tareasEjecucionConstraints (id, idTask1, idTask2, type, relationType, idPlanningConstraint) VALUES (:id, :idTask1, :idTask2, :type, :relationType, :idPlanningConstraint);");
        query->bindValue(":id", id());
        query->bindValue(":idTask1", _idTask1);
        query->bindValue(":idTask2", _idTask2);
        query->bindValue(":type", _Type);
        query->bindValue(":relationType", _RelationType);
        query->bindValue(":idPlanningConstraint", _idPlanningConstraint);
        break;
    }
    case EntityStatus::deleted:
    {
        query = new QSqlQuery(database);
        query->prepare("DELETE FROM tareasEjecucionConstraints WHERE id = :id;");
        query->bindValue(":id", id());
        break;
    }
    case EntityStatus::modified:
    {
        query = new QSqlQuery(database);
        query->prepare("UPDATE tareasEjecucionConstraints SET idTask1 = :idTask1, idTask2 = :idTask2, type = :type, relationType = :relationType, idPlanningConstraint = :idPlanningConstraint WHERE id = :id;");
        query->bindValue(":idTask1", _idTask1);
        query->bindValue(":idTask2", _idTask2);
        query->bindValue(":type", _Type);
        query->bindValue(":relationType", _RelationType);
        query->bindValue(":idPlanningConstraint", _idPlanningConstraint);
        query->bindValue(":id", id());
        break;
    }
    case EntityStatus::unchanged:
        query = NULL;
        break;
    }
    return query;
}

void ExecutionTaskConstraint::setPlanningTaskConstraint(EntityBasePtr entity, bool copyData)
{
    _idPlanningConstraint = entity->id();
    if (copyData)
    {
        PlanningTaskConstraintPtr ptc = qSharedPointerDynamicCast<PlanningTaskConstraint>(entity);
        setIdTask1(ptc->idTask1());
        setIdTask2(ptc->idTask2());
        setType(ptc->Type());
        setRelationType(ptc->RelationType());
    }
}
