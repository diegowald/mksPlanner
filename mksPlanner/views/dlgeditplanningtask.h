#ifndef DLGEDITPLANNINGTASK_H
#define DLGEDITPLANNINGTASK_H

#include <QDialog>
#include "models/planningtaskmodel.h"
#include "models/materialfiltermodel.h"
#include "models/proveedorbyrubrofiltermodel.h"
#include "models/planningtaskmodelconstraintfiltered.h"


namespace Ui {
class DlgEditPlanningTask;
}

class DlgEditPlanningTask : public QDialog
{
    Q_OBJECT

public:
    explicit DlgEditPlanningTask(PlanningTaskModel* model, EntityBasePtr entity, QWidget *parent = 0);

    ~DlgEditPlanningTask();

private slots:
    void on_buttonBox_accepted();

    void on_cboTarea_currentIndexChanged(int index);

private:
    int idRubroMaterialSeleccionado();
    void fillTaskTypes();

private:
    Ui::DlgEditPlanningTask *ui;
    PlanningTaskModel *_model;
    EntityBasePtr _entity;
    MaterialFilterModel *_materialFilterModel;
    ProveedorByRubroFilterModel *_proveedorByRubroFilterModel;
    PlanningTaskModelConstraintFiltered *_constraintsFiltered;
};

#endif // DLGEDITPLANNINGTASK_H
