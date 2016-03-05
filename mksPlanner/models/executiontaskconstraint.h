#ifndef EXECUTIONTASKCONSTRAINT_H
#define EXECUTIONTASKCONSTRAINT_H

#include <QObject>
#include "models/entitybase.h"

class ExecutionTaskConstraint : public EntityBase
{
    Q_OBJECT
public:
    explicit ExecutionTaskConstraint(int id);

    explicit ExecutionTaskConstraint(int id, int idTask1, int idTask2, int Type, int RelationType, int idPlanningTaskConstraint);

    virtual QString toDebugString();

    virtual QSqlQuery* getQuery(QSqlDatabase &database);

    void setPlanningTaskConstraint(EntityBasePtr entity, bool copyData);

    int idTask1() const;
    int idTask2() const;
    int Type() const;
    int RelationType() const;

    void setIdTask1(int value);
    void setIdTask2(int value);
    void setType(int value);
    void setRelationType(int value);

signals:

public slots:

private:
    int _idTask1;
    int _idTask2;
    int _Type;
    int _RelationType;
    int _idPlanningConstraint;
};

typedef QSharedPointer<ExecutionTaskConstraint> ExecutionTaskConstraintPtr;

#endif // EXECUTIONTASKCONSTRAINT_H
