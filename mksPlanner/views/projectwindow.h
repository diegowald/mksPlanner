#ifndef PROJECTWINDOW_H
#define PROJECTWINDOW_H

#include <QMainWindow>
#include <QDataWidgetMapper>

#include "models/modelbase.h"
#include "models/planningtaskmodeladapter.h"
#include "models/planningtaskmodelconstraintadapter.h"
#include "models/executiontaskmodeladapter.h"
#include "models/executiontaskmodelconstraintadapter.h"
#include "KDGantt"

namespace Ui {
class ProjectWindow;
}

class ProjectWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ProjectWindow(const QString &windowTitle, int idInterno, QWidget *parent = 0);
    ~ProjectWindow();

    void setModel(ModelBase* model);
    void setPlanningModel(ModelBase *model);
    void setConstraintModel(ModelBase *model);
    void setIconResource(const QString &resourceName);

    void setExecutionModel(ModelBase *model);
    void setExecutionConstraintModel(ModelBase *model);

private slots:
    void on_tabWidget_currentChanged(int index);

    void on_actionAddTask_triggered();

    void on_actionEdit_Task_triggered();

    void on_actionRemove_Task_triggered();

    void on_actionGuardar_cambios_triggered();
    void on_modelChanged(Tables table);
    void on_PlanningModelChanged(Tables table);
    void on_TreeView_doubleClicked(const QModelIndex &index);
    void on_TreeViewExecution_doubleClicked(const QModelIndex &index);

    void on_actionActionAddSubTask_triggered();

    void on_btnEjecucion_released();

    void on_btnPausa_released();

    void on_btnFin_released();

private:
    void updateEstimacionMateriales();
    void updateBotonesEstados();
private:
    Ui::ProjectWindow *ui;
    ModelBase* _model;
    QDataWidgetMapper *_mapper;
    PlanningTaskModelAdapter *_planningModel;
    PlanningTaskModelConstraintAdapter *_constraintModel;
    ExecutionTaskModelAdapter *_executionModel;
    ExecutionTaskModelConstraintAdapter *_execConstraintModel;

    int _idInterno;
};

#endif // PROJECTWINDOW_H
