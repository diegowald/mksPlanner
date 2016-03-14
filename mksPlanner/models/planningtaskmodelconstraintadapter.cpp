#include "planningtaskmodelconstraintadapter.h"
#include <KDGantt>
#include "models/planningtaskconstraint.h"

PlanningTaskModelConstraintAdapter::PlanningTaskModelConstraintAdapter(PlanningTaskModelAdapter *planningModel, ModelBase *constraintModel, QObject *parent)
    : KDGantt::ConstraintModel(parent)
{
    _planningModel = planningModel;
    _model = constraintModel;
    connect(_model, &ModelBase::dataChanged, this, &PlanningTaskModelConstraintAdapter::on_dataChanged);
    createConstraints();
}

void PlanningTaskModelConstraintAdapter::createConstraints()
{
    int rowCount = _model->rowCount(QModelIndex());
    for (int i = 0; i < rowCount; ++i)
    {
        PlanningTaskConstraintPtr pt = qSharedPointerDynamicCast<PlanningTaskConstraint>(_model->getItemByRowid(i));
        QModelIndex startTask = _planningModel->index(pt->idTask1());
        QModelIndex endTask = _planningModel->index(pt->idTask2());
        KDGantt::Constraint::Type type = static_cast<KDGantt::Constraint::Type>(pt->Type());
        KDGantt::Constraint::RelationType relType = static_cast<KDGantt::Constraint::RelationType>(pt->RelationType());
        KDGantt::Constraint c(startTask, endTask, type, relType);
        addConstraint(c);
    }
}

void PlanningTaskModelConstraintAdapter::on_dataChanged(const QModelIndex &, const QModelIndex &, const QVector<int> &)
{
    clear();
    createConstraints();
}
