#include "planningtaskconstraint.h"
#include <QSqlQuery>
#include <QVariant>

PlanningTaskConstraint::PlanningTaskConstraint(int id) : EntityBase(id, true)
{
    _idTask1 = -1;
    _idTask2 = -1;
    _Type = -1;
    _RelationType = -1;
}

PlanningTaskConstraint::PlanningTaskConstraint(int id, int idTask1, int idTask2, int Type, int RelationType) : EntityBase(id)
{
    _idTask1 = idTask1;
    _idTask2 = idTask2;
    _Type = Type;
    _RelationType = RelationType;
}

int PlanningTaskConstraint::idTask1() const
{
    return _idTask1;
}

int PlanningTaskConstraint::idTask2() const
{
    return _idTask2;
}

int PlanningTaskConstraint::Type() const
{
    return _Type;
}

int PlanningTaskConstraint::RelationType() const
{
    return _RelationType;
}

void PlanningTaskConstraint::setIdTask1(int value)
{
    _idTask1 = value;
    updateStatus();
}

void PlanningTaskConstraint::setIdTask2(int value)
{
    _idTask2 = value;
    updateStatus();
}

void PlanningTaskConstraint::setType(int value)
{
    _Type = value;
    updateStatus();
}

void PlanningTaskConstraint::setRelationType(int value)
{
    _RelationType = value;
    updateStatus();
}

QString PlanningTaskConstraint::toDebugString()
{
    return QString("De %1 a %2. Tipo %3. Relation Type: %4").arg(_idTask1)
            .arg(_idTask2).arg(_Type).arg(_RelationType);
}


QSqlQuery* PlanningTaskConstraint::getQuery(QSqlDatabase &database)
{
    QSqlQuery *query = NULL;
    switch (status())
    {
    case EntityStatus::added:
    {
        query = new QSqlQuery(database);
        query->prepare("INSERT INTO tareasPlanificadasConstraints (id, idTask1, idTask2, type, relationType) VALUES (:id, :idTask1, :idTask2, :type, :relationType);");
        query->bindValue(":id", id());
        query->bindValue(":idTask1", _idTask1);
        query->bindValue(":idTask2", _idTask2);
        query->bindValue(":type", _Type);
        query->bindValue(":relationType", _RelationType);
        break;
    }
    case EntityStatus::deleted:
    {
        query = new QSqlQuery(database);
        query->prepare("DELETE FROM tareasPlanificadasConstraints WHERE id = :id;");
        query->bindValue(":id", id());
        break;
    }
    case EntityStatus::modified:
    {
        query = new QSqlQuery(database);
        query->prepare("UPDATE tareasPlanificadasConstraints SET idTask1 = :idTask1, idTask2 = :idTask2, type = :type, relationType = :relationType WHERE id = :id;");
        query->bindValue(":idTask1", _idTask1);
        query->bindValue(":idTask2", _idTask2);
        query->bindValue(":type", _Type);
        query->bindValue(":relationType", _RelationType);
        query->bindValue(":id", id());
        break;
    }
    case EntityStatus::unchanged:
        query = NULL;
        break;
    }
    return query;
}
