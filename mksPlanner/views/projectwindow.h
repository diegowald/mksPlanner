#ifndef PROJECTWINDOW_H
#define PROJECTWINDOW_H

#include <QMainWindow>
#include <QDataWidgetMapper>

#include "models/modelbase.h"
#include "models/planningtaskmodeladapter.h"
#include "models/planningtaskmodelconstraintadapter.h"
#include "models/executiontaskmodeladapter.h"
#include "models/executiontaskmodelconstraintadapter.h"
#include "models/certificacionesmodel.h"
#include "models/modelfilter.h"
#include "KDGantt"
#include "persistance/projectlibrary.h"
#include "models/certificadosmodel.h"

namespace Ui {
class ProjectWindow;
}

class ProjectWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ProjectWindow(const QString &windowTitle, int idInterno, QWidget *parent = 0);
    ~ProjectWindow();

    void setProjectLibrary(ProjectLibrary *library);
    void setIconResource(const QString &resourceName);

protected:
    void setModel(IModel *model);
    void setPlanningModel(IModel *model);
    void setConstraintModel(IModel *model);

    void setExecutionModel(IModel *model);
    void setExecutionConstraintModel(IModel *model);

    void setCertificacionesModel(IModel *model);

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
    void on_TreeViewExecution_clicked(const QModelIndex &index);

    void on_actionActionAddSubTask_triggered();

    void on_btnEjecucion_released();

    void on_btnPausa_released();

    void on_btnFin_released();

    void on_actionInterrumpir_Ejecucion_Tarea_triggered();

    void on_actionNueva_Certificacion_triggered();

    void on_actionEditar_Certificacion_triggered();

    void on_actionBorrar_Ceritificacion_triggered();

    void on_tblCertificaciones_selectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
    void on_tblCertificados_selectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
    void on_tblCertificacionesNoEmitidas_selectionChanged(const QItemSelection &selected, const QItemSelection &deselected);

    void on_btnAbonado_released();

    void on_btnEmitido_released();

    void on_btnVerCertificadoClienteEnProceso_toggled(bool checked);

    void on_actionAddExecutionSubTask_triggered();

    void on_actionAddExecutionTask_triggered();

    void on_actionEditExecutionTask_triggered();

    void on_actionDeleteExecutionTask_triggered();

    void on_actionImprimir_triggered();

private:
    void updateEstimacionMateriales();
    void updateEstimacionMaterialesCertificacion(int idCertificacion);

    void updateBotonesEstados();
    void checkSplitAction();

    void updateCertificacionView(EntityBasePtr certificacion);
    void recalcularTotalesCertificado(EntityBasePtr certificacion);
    void certificarTareasEnEjecucion(EntityBasePtr certificaion);

private:
    Ui::ProjectWindow *ui;
    IModel* _model;
    QDataWidgetMapper *_mapper;
    ProjectLibrary *_projectLibrary;
    PlanningTaskModelAdapter *_planningModel;
    PlanningTaskModelConstraintAdapter *_constraintModel;
    ExecutionTaskModelAdapter *_executionModel;
    ExecutionTaskModelConstraintAdapter *_execConstraintModel;
    CertificacionesModel *_certificacionesModel;
    ModelFilter *_tareasCertificacionEnProceso;
    ModelFilter *_tareasCertificadoEnProceso;
    ModelFilter *_certificadosEnProceso;


    ModelFilter *_certificadosHechosModel;
    ModelFilter *_tareasCertificadoHechosModel;

    ModelFilter *_certificacionesNoEmitidas;

    QDataWidgetMapper *_certificadoMapper;

    int _idInterno;
    QModelIndex _selectedExecutionIndex;

    int _idCertificacionSeleccionada;
    int _idProveedorSeleccionado;

};

#endif // PROJECTWINDOW_H
