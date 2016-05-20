#include "executiontaskmodelconstraintadapter.h"
#include <KDGantt>
#include "models/executiontaskconstraint.h"
#include "models/executiontaskmodelconstraint.h"


ExecutionTaskModelConstraintAdapter::ExecutionTaskModelConstraintAdapter(ExecutionTaskModelAdapter *execModel, IModel *constraintModel, QObject *parent)
    : KDGantt::ConstraintModel(parent)
{
    _execModel = execModel;
    _model = constraintModel;
    connect(_model, &ModelBase::dataChanged, this, &ExecutionTaskModelConstraintAdapter::on_dataChanged);
    ExecutionTaskModelConstraint *m = qobject_cast<ExecutionTaskModelConstraint *>(_model);
    connect(m, &ExecutionTaskModelConstraint::refreshed, this, &ExecutionTaskModelConstraintAdapter::createConstraints);
    createConstraints();
}

void ExecutionTaskModelConstraintAdapter::createConstraints()
{
    int rowCount = _model->rowCount(QModelIndex());
    for (int i = 0; i < rowCount; ++i)
    {
        ExecutionTaskConstraintPtr pt = qSharedPointerDynamicCast<ExecutionTaskConstraint>(_model->getItemByRowid(i));
        QModelIndex startTask = _execModel->index(_execModel->idFromPlanning(pt->idTask1()));
        QModelIndex endTask = _execModel->index(_execModel->idFromPlanning(pt->idTask2()));
        KDGantt::Constraint::Type type = static_cast<KDGantt::Constraint::Type>(pt->Type());
        KDGantt::Constraint::RelationType relType = static_cast<KDGantt::Constraint::RelationType>(pt->RelationType());
        KDGantt::Constraint c(startTask, endTask, type, relType);
        addConstraint(c);
    }
}

void ExecutionTaskModelConstraintAdapter::on_dataChanged(const QModelIndex &, const QModelIndex &, const QVector<int> &)
{
    clear();
    createConstraints();
}


void ExecutionTaskModelConstraintAdapter::refresh()
{
    clear();
    createConstraints();
}
