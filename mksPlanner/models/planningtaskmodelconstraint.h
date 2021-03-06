#ifndef PLANNINGTASKMODELCONSTRAINT_H
#define PLANNINGTASKMODELCONSTRAINT_H

#include <QObject>
#include "models/modelbase.h"
#include "models/planningtaskconstraint.h"

class PlanningTaskModelConstraint : public ModelBase
{
    Q_OBJECT
public:
    explicit PlanningTaskModelConstraint(int idProyecto, QObject *parent = 0);

signals:

public slots:

    // PersisterBase interface
protected:
    virtual QString _getSQLRead() const;
    virtual int _loadEntity(QSqlRecord record);

    // ModelBase interface
public:
    virtual void editEntity(int row);

protected:
    virtual EntityBasePtr internalCreateEntity(int assignedId);
    virtual QVariant modelData(EntityBasePtr entity, int column, int role) const;
    virtual bool modelSetData(EntityBasePtr entity, int column, const QVariant &value, int role);

private:
    PlanningTaskConstraintPtr cast(EntityBasePtr entity);

    // PersisterBase interface
protected:
    virtual void postProcessData();

    // ModelBase interface
protected:
    virtual void defineColumnNames();

private:
    int _idProyecto;

};

#endif // PLANNINGTASKMODELCONSTRAINT_H
