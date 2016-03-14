#ifndef PLANNINGTASKMODELCONSTRAINTFILTERED_H
#define PLANNINGTASKMODELCONSTRAINTFILTERED_H

#include "models/planningtaskmodelconstraint.h"
#include "models/planningtaskconstraint.h"


class PlanningTaskModelConstraintFiltered : public ModelBase
{
    Q_OBJECT
public:
    explicit PlanningTaskModelConstraintFiltered(int idProyecto, int idTask, PlanningTaskModelConstraint *model,  QObject *parent = 0);

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    virtual EntityBasePtr getItemByRowid(int row);
    virtual bool removeRow(int row, const QModelIndex &parent);
private:
    void extractIds();

protected:
    virtual EntityBasePtr internalCreateEntity(int assignedId);

signals:

public slots:
private:
    int _idProyecto;
    int _idTask;
    PlanningTaskModelConstraint *_model;
    QList<int> _ids;

    // PersisterBase interface
protected:
    virtual QString _getSQLRead() const;
    virtual int _loadEntity(QSqlRecord record);

    // ModelBase interface
public:
    virtual void editEntity(int row);

private:
    PlanningTaskConstraintPtr cast(EntityBasePtr entity);

protected:
    virtual QVariant modelData(EntityBasePtr entity, int column, int role) const;
    virtual bool modelSetData(EntityBasePtr entity, int column, const QVariant &value, int role);
};

#endif // PLANNINGTASKMODELCONSTRAINTFILTERED_H
