#ifndef EXECUTIONTASKMODELCONSTRAINT_H
#define EXECUTIONTASKMODELCONSTRAINT_H

#include <QObject>
#include "models/modelbase.h"

class ExecutionTaskModelConstraint : public ModelBase
{
    Q_OBJECT
public:
    explicit ExecutionTaskModelConstraint(int idProyecto, QObject *parent = 0);

signals:

public slots:

    // PersisterBase interface
protected:
    virtual QString _getSQLRead() const;
    virtual int _loadEntity(QSqlRecord record);

    // ModelBase interface
public:
    virtual void editEntity(int row);
    void cloneFromPlanning();


protected:
    virtual EntityBasePtr internalCreateEntity(int assignedId);
    virtual QVariant modelData(EntityBasePtr entity, int column, int role) const;
    virtual bool modelSetData(EntityBasePtr entity, int column, const QVariant &value, int role);

    // PersisterBase interface
protected:
    virtual void postProcessData();

    // ModelBase interface
protected:
    virtual void defineColumnNames();

private:
    int _idProyecto;
};

#endif // EXECUTIONTASKMODELCONSTRAINT_H
