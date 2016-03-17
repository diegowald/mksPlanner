#ifndef PLANNINGTASKMODELCONSTRAINTADAPTER_H
#define PLANNINGTASKMODELCONSTRAINTADAPTER_H

#include <QObject>
#include <KDGantt>
#include "modelbase.h"
#include "models/planningtaskmodeladapter.h"


class PlanningTaskModelConstraintAdapter : public KDGantt::ConstraintModel
{
    Q_OBJECT
public:
    explicit PlanningTaskModelConstraintAdapter(PlanningTaskModelAdapter *planningModel, IModel* constraintModel, QObject *parent = 0);

private slots:
    void on_dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles);

private:
    void createConstraints();
private:
    PlanningTaskModelAdapter *_planningModel;
    IModel *_model;
};

#endif // PLANNINGTASKMODELCONSTRAINTADAPTER_H
