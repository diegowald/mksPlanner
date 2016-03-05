#ifndef EXECUTIONTASKMODELCONSTRAINTADAPTER_H
#define EXECUTIONTASKMODELCONSTRAINTADAPTER_H

#include <QObject>
#include <KDGantt>
#include "modelbase.h"
#include "models/executiontaskmodeladapter.h"

class ExecutionTaskModelConstraintAdapter : public KDGantt::ConstraintModel
{
    Q_OBJECT
public:
    explicit ExecutionTaskModelConstraintAdapter(ExecutionTaskModelAdapter *execModel, ModelBase* constraintModel, QObject *parent = 0);

private slots:
    void on_dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles);

private:
    void createConstraints();
private:
    ExecutionTaskModelAdapter *_execModel;
    ModelBase *_model;
};
#endif // EXECUTIONTASKMODELCONSTRAINTADAPTER_H
