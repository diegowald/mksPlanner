#ifndef DLGEDITEXECUTIONTASK_H
#define DLGEDITEXECUTIONTASK_H

#include <QDialog>
#include "models/executiontaskmodel.h"
#include "models/materialfiltermodel.h"
#include "models/proveedorbyrubrofiltermodel.h"
#include "models/executiontaskmodelconstraintfiltered.h"

namespace Ui {
class DlgEditExecutionTask;
}

class DlgEditExecutionTask : public QDialog
{
    Q_OBJECT

public:
    explicit DlgEditExecutionTask(ExecutionTaskModel* model, EntityBasePtr entity, QWidget *parent = 0);
    ~DlgEditExecutionTask();

private slots:
    void on_buttonBox_accepted();

    void on_cboTarea_currentIndexChanged(int index);

    void on_cboTaskType_currentIndexChanged(int index);

private:
    int idRubroMaterialSeleccionado();
    void fillTaskTypes();

private:
    Ui::DlgEditExecutionTask *ui;
    ExecutionTaskModel *_model;
    EntityBasePtr _entity;
    MaterialFilterModel *_materialFilterModel;
    ProveedorByRubroFilterModel *_proveedorByRubroFilterModel;
    ExecutionTaskModelConstraintFiltered *_constraintsFiltered;

};

#endif // DLGEDITEXECUTIONTASK_H
