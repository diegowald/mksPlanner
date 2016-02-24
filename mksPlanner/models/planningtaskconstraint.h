#ifndef PLANNINGTASKCONSTRAINT_H
#define PLANNINGTASKCONSTRAINT_H

#include <QObject>
#include "models/entitybase.h"

class PlanningTaskConstraint : public EntityBase
{
    Q_OBJECT
public:
    explicit PlanningTaskConstraint(int id);
    explicit PlanningTaskConstraint(int id, int idTask1, int idTask2, int Type, int RelationType);

    virtual QString toDebugString();

    virtual QSqlQuery* getQuery(QSqlDatabase &database);


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
};

typedef QSharedPointer<PlanningTaskConstraint> PlanningTaskConstraintPtr;

#endif // PLANNINGTASKCONSTRAINT_H
