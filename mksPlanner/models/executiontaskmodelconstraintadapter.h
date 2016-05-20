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
    explicit ExecutionTaskModelConstraintAdapter(ExecutionTaskModelAdapter *execModel, IModel* constraintModel, QObject *parent = 0);

    void refresh();

private slots:
    void on_dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles);
    void createConstraints();

private:
    ExecutionTaskModelAdapter *_execModel;
    IModel *_model;
};
#endif // EXECUTIONTASKMODELCONSTRAINTADAPTER_H
