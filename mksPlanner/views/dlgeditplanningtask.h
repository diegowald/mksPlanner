#ifndef DLGEDITPLANNINGTASK_H
#define DLGEDITPLANNINGTASK_H

#include <QDialog>
#include <QDataWidgetMapper>
#include "models/planningtaskmodel.h"
#include "models/materialfiltermodel.h"
#include "models/proveedorbyrubrofiltermodel.h"

namespace Ui {
class DlgEditPlanningTask;
}

class DlgEditPlanningTask : public QDialog
{
    Q_OBJECT

public:
    explicit DlgEditPlanningTask(PlanningTaskModel* model, int selectedEntity, QWidget *parent = 0);

    ~DlgEditPlanningTask();

private slots:
    void on_buttonBox_accepted();

    void on_cboTarea_currentIndexChanged(int index);

private:
    int idRubroMaterialSeleccionado();

private:
    Ui::DlgEditPlanningTask *ui;
    PlanningTaskModel *_model;
    QDataWidgetMapper *_mapper;
    EntityBasePtr _entity;
    MaterialFilterModel *_materialFilterModel;
    ProveedorByRubroFilterModel *_proveedorByRubroFilterModel;
};

#endif // DLGEDITPLANNINGTASK_H