#ifndef EXECUTIONTASKMODELCONSTRAINTFILTERED_H
#define EXECUTIONTASKMODELCONSTRAINTFILTERED_H

#include "models/executiontaskmodelconstraint.h"

class ExecutionTaskModelConstraintFiltered : public ModelBase
{
    Q_OBJECT
public:
    explicit ExecutionTaskModelConstraintFiltered(int idProyecto, int idTask, ExecutionTaskModelConstraint *model,  QObject *parent = 0);

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    virtual EntityBasePtr getItemByRowid(int row);

private:
    void extractIds();

protected:
    virtual EntityBasePtr internalCreateEntity(int assignedId);

signals:

public slots:
private:
    int _idProyecto;
    int _idTask;
    ExecutionTaskModelConstraint *_model;
    QList<int> _ids;

    // PersisterBase interface
protected:
    virtual QString _getSQLRead() const;
    virtual int _loadEntity(QSqlRecord record);

    // ModelBase interface
public:
    virtual void editEntity(int row);

protected:
    virtual QVariant modelData(EntityBasePtr entity, int column, int role) const;
    virtual bool modelSetData(EntityBasePtr entity, int column, const QVariant &value, int role);

};

#endif // EXECUTIONTASKMODELCONSTRAINTFILTERED_H
