#include "projectwindow.h"
#include "ui_projectwindow.h"
#include <QTreeView>
#include "models/proyectomodel.h"
#include "globalcontainer.h"
#include "models/planningtask.h"
#include "models/proyecto.h"


ProjectWindow::ProjectWindow(const QString &windowTitle, int idInterno, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ProjectWindow)
{
    ui->setupUi(this);
    setWindowTitle(windowTitle);
    _mapper = NULL;
    _idInterno = idInterno;
    _model = NULL;
    _planningModel = NULL;
    _constraintModel = NULL;
    _executionModel = NULL;
}

ProjectWindow::~ProjectWindow()
{
    delete ui;
}


void ProjectWindow::setModel(IModel *model)
{
    _model = model;
    if (_mapper != NULL)
    {
        _mapper->deleteLater();
    }

    _mapper = new QDataWidgetMapper(this);
    _mapper->setModel(model);

    _mapper->addMapping(ui->txtPropietario, model->columnIndex("Propietario"));
    _mapper->addMapping(ui->txtDireccion, model->columnIndex("Direccion"));
    _mapper->addMapping(ui->txtEmail, model->columnIndex("Email"));
    _mapper->addMapping(ui->txtTelefono, model->columnIndex("Telefono"));
    _mapper->addMapping(ui->dateEstimacionInicio, model->columnIndex("Fecha estimada de Inicio"));
    _mapper->addMapping(ui->dateEstimacionFinalizacion, model->columnIndex("Fecha estimada de finalización"));
    _mapper->addMapping(ui->txtPlazo, model->columnIndex("Plazo"));
    _mapper->addMapping(ui->txtCosto, model->columnIndex("Costo"));

    _mapper->setCurrentIndex(0);
    _mapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);

    updateBotonesEstados();
    ui->tabWidget->setCurrentIndex(1);
    ui->tabWidget->setCurrentIndex(0);

    ui->tabWidget->setTabEnabled(3, false);

    ui->lblFilename->setText(qobject_cast<ProyectoModel*>(model)->filename());
    connect(static_cast<ModelBase*>(model), &ModelBase::changed, this, &ProjectWindow::on_modelChanged);
}

void ProjectWindow::setPlanningModel(IModel *model)
{
    _planningModel = new PlanningTaskModelAdapter(qobject_cast<PlanningTaskModel*>(model), this);
    _planningModel->setProyecto(_model->getItem(1));
    ui->planningView->setModel(_planningModel);
    ui->planningView->setSelectionModel( new QItemSelectionModel(_planningModel));

    ui->planningView->leftView()->setHorizontalScrollBarPolicy( Qt::ScrollBarAsNeeded );
    ui->planningView->graphicsView()->setHorizontalScrollBarPolicy( Qt::ScrollBarAsNeeded );

    KDGantt::DateTimeGrid *grid = new KDGantt::DateTimeGrid();
    grid->setDayWidth(35);
    grid->setWeekStart(Qt::Sunday);
    grid->setScale(KDGantt::DateTimeGrid::ScaleDay);

    ui->planningView->setGrid(grid);

    QTreeView *tv = qobject_cast<QTreeView*>(ui->planningView->leftView());
    Q_ASSERT(tv);
    tv->setColumnHidden(1, true);
    tv->setColumnHidden(4, true);

    connect(tv, &QTreeView::doubleClicked, this, &ProjectWindow::on_TreeView_doubleClicked);
    ui->actionAddTask->setEnabled(model->canCreateEntity());
    connect(static_cast<ModelBase*>(model), &ModelBase::changed, this, &ProjectWindow::on_PlanningModelChanged);
    updateEstimacionMateriales();
}

void ProjectWindow::setConstraintModel(IModel *model)
{
    _constraintModel = new PlanningTaskModelConstraintAdapter(_planningModel, model, this);
//    KDGantt::Constraint c;
    //_constraintModel = model;
    ui->planningView->setConstraintModel(_constraintModel);
}

void ProjectWindow::setExecutionModel(IModel *model)
{
    _executionModel = new ExecutionTaskModelAdapter(qobject_cast<ExecutionTaskModel*>(model), this);
    _executionModel->setProyecto(_model->getItem(1));
    ui->executionView->setModel(_executionModel);
    ui->executionView->setSelectionModel(new QItemSelectionModel(_executionModel));

    ui->executionView->leftView()->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->executionView->graphicsView()->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    KDGantt::DateTimeGrid *grid = new KDGantt::DateTimeGrid();
    grid->setDayWidth(35);
    grid->setWeekStart(Qt::Sunday);
    grid->setScale(KDGantt::DateTimeGrid::ScaleDay);

    ui->executionView->setGrid(grid);

    QTreeView *tv = qobject_cast<QTreeView*>(ui->executionView->leftView());

    Q_ASSERT(tv);
    tv->setColumnHidden(1, true);

    connect(tv, &QTreeView::doubleClicked, this, &ProjectWindow::on_TreeViewExecution_doubleClicked);
    connect(tv, &QTreeView::clicked, this, &ProjectWindow::on_TreeViewExecution_clicked);
}

void ProjectWindow::setExecutionConstraintModel(IModel *model)
{
    _execConstraintModel = new ExecutionTaskModelConstraintAdapter(_executionModel, model, this);
    ui->executionView->setConstraintModel(_execConstraintModel);
}

void ProjectWindow::on_tabWidget_currentChanged(int index)
{
    ui->actionAddTask->setVisible(index == 1);
    ui->actionEdit_Task->setVisible(index == 1);
    ui->actionRemove_Task->setVisible(index == 1);
    ui->actionActionAddSubTask->setVisible(index == 1);
    ui->actionAddExecutionTask->setVisible(index == 3);
    ui->actionAddExecutionSubTask->setVisible(index == 3);
    ui->actionEditExecutionTask->setVisible(index == 3);
    ui->actionDeleteExecutionTask->setVisible(index == 3);
    ui->actionInterrumpir_Ejecucion_Tarea->setVisible(index == 3);
    ui->actionNueva_Certificacion->setVisible(index == 4);
    ui->actionEditar_Certificacion->setVisible(index == 4);
    ui->actionBorrar_Ceritificacion->setVisible(index == 4);

    checkSplitAction();
}

void ProjectWindow::on_actionAddTask_triggered()
{
    int rowCount = ui->planningView->model()->rowCount();

    QModelIndex index = ui->planningView->selectionModel()->currentIndex();


    if (!_planningModel->insertRow(rowCount, index.parent()))
        return;

    _planningModel->editEntity(rowCount);
}

void ProjectWindow::on_actionActionAddSubTask_triggered()
{
    QModelIndex idx = ui->planningView->selectionModel()->currentIndex();
    if (idx.isValid())
    {
        qDebug() << "MainWindow::slotToolsNewItem" << idx;
        if (!_planningModel->insertRow(1, _planningModel->index(idx.row(), 0, idx.parent())))
            return;

        //_planningModel->insertRows(0, 1, _planningModel->index(idx.row(), 0, idx.parent()));
        //_planningModel->editEntity(_planningModel->index(idx.row(), 0, idx.parent()).child(0, 0));
    }
}

void ProjectWindow::on_actionEdit_Task_triggered()
{
    QModelIndex index = ui->planningView->selectionModel()->currentIndex();
    _planningModel->editEntity(index);
}

void ProjectWindow::on_actionRemove_Task_triggered()
{
    QModelIndex index = ui->planningView->selectionModel()->currentIndex();
    _planningModel->removeEntity(window(), index);
}

void ProjectWindow::on_actionGuardar_cambios_triggered()
{
    GlobalContainer::instance().projectLibrary(_idInterno)->save();
}

void ProjectWindow::on_modelChanged(Tables)
{

}

void ProjectWindow::on_PlanningModelChanged(Tables)
{
    ui->actionAddTask->setEnabled(_planningModel->canCreateEntity());
    updateEstimacionMateriales();
}

void ProjectWindow::on_TreeView_doubleClicked(const QModelIndex &index)
{
    if (index.isValid())
       _planningModel->editEntity(index);
}

void ProjectWindow::on_TreeViewExecution_doubleClicked(const QModelIndex &index)
{
    if (index.isValid())
       _executionModel->editEntity(index);
}

void ProjectWindow::on_TreeViewExecution_clicked(const QModelIndex &index)
{
    _selectedExecutionIndex = index;
    checkSplitAction();
}

void ProjectWindow::checkSplitAction()
{
    bool canSplit = false;
    if (_selectedExecutionIndex.isValid())
    {
        canSplit = _executionModel->canBeSplitted(_selectedExecutionIndex);
    }
    ui->actionInterrumpir_Ejecucion_Tarea->setEnabled(canSplit);
}

void ProjectWindow::updateEstimacionMateriales()
{
    ui->tblEstimacionMateriales->setRowCount(0);
    ui->tblEstimacionMateriales->setColumnCount(3);
    ui->tblEstimacionMateriales->setHorizontalHeaderItem(0, new QTableWidgetItem(tr("Material")));
    ui->tblEstimacionMateriales->setHorizontalHeaderItem(1, new QTableWidgetItem(tr("Cantidad")));
    ui->tblEstimacionMateriales->setHorizontalHeaderItem(2, new QTableWidgetItem(tr("Unidad")));
    QMap<QString, CantidadPtr> results;
    int rowCount = _planningModel->rowCount(QModelIndex());
    for (int i = 0; i < rowCount; ++i)
    {
        EntityBasePtr entity = _planningModel->itemByRowId(i);
        PlanningTaskPtr pt = qSharedPointerDynamicCast<PlanningTask>(entity);
        QMap<QString, CantidadPtr> partialResult = pt->listadoMateriales();
        foreach (QString material, partialResult.keys())
        {
            if (!results.contains(material))
            {
                results[material] = partialResult[material];
            }
            else
            {
                CantidadPtr c = results[material];
                c->setValue(c->value() + partialResult[material]->value());
            }
        }
    }

    foreach (QString material, results.keys())
    {
        int row = ui->tblEstimacionMateriales->rowCount();
        ui->tblEstimacionMateriales->insertRow(row);
        ui->tblEstimacionMateriales->setItem(row, 0, new QTableWidgetItem(material));
        ui->tblEstimacionMateriales->setItem(row, 1, new QTableWidgetItem(results[material]->toString()));
    }
}


void ProjectWindow::setIconResource(const QString &resourceName)
{
    QPixmap px;
    px.load(resourceName);
    QIcon icon(px);
    setWindowIcon(icon);
}


void ProjectWindow::updateBotonesEstados()
{
    EntityBasePtr entity = _model->getItemByRowid(0);
    ProyectoPtr proyecto = qSharedPointerDynamicCast<Proyecto>(entity);

    ui->btnEjecucion->setVisible(false);
    ui->btnFin->setVisible(false);
    ui->btnPausa->setVisible(false);

    switch (proyecto->projectStatus())
    {
    case Proyecto::ProjectStatus::Planificacion:
        ui->lblEstadoActual->setText("Planificación");
        ui->btnEjecucion->setVisible(true);
        ui->tabWidget->setTabEnabled(3, false);
        ui->tabWidget->setTabEnabled(4, false);
        break;
    case Proyecto::ProjectStatus::Ejecucion:
        ui->lblEstadoActual->setText("Ejecución");
        ui->btnFin->setVisible(true);
        ui->btnPausa->setVisible(true);
        ui->tabWidget->setTabEnabled(3, true);
        ui->tabWidget->setTabEnabled(4, true);
        break;
    case Proyecto::ProjectStatus::Pausado:
        ui->lblEstadoActual->setText("Pausa");
        ui->btnEjecucion->setVisible(true);
        ui->tabWidget->setTabEnabled(3, true);
        ui->tabWidget->setTabEnabled(4, true);
        break;
    case Proyecto::ProjectStatus::Finalizado:
        ui->lblEstadoActual->setText("Finalizado");
        ui->tabWidget->setTabEnabled(3, true);
        ui->tabWidget->setTabEnabled(4, true);
        break;
    default:
        ui->lblEstadoActual->setText("");
        break;
    }
}

void ProjectWindow::on_btnEjecucion_released()
{
    EntityBasePtr entity = _model->getItemByRowid(0);
    ProyectoPtr proyecto = qSharedPointerDynamicCast<Proyecto>(entity);
    proyecto->setProjectStatus(Proyecto::ProjectStatus::Ejecucion);
    updateBotonesEstados();
}


void ProjectWindow::on_btnPausa_released()
{
    EntityBasePtr entity = _model->getItemByRowid(0);
    ProyectoPtr proyecto = qSharedPointerDynamicCast<Proyecto>(entity);
    proyecto->setProjectStatus(Proyecto::ProjectStatus::Pausado);
    updateBotonesEstados();
}

void ProjectWindow::on_btnFin_released()
{
    EntityBasePtr entity = _model->getItemByRowid(0);
    ProyectoPtr proyecto = qSharedPointerDynamicCast<Proyecto>(entity);
    proyecto->setProjectStatus(Proyecto::ProjectStatus::Finalizado);
    updateBotonesEstados();
}

void ProjectWindow::on_actionInterrumpir_Ejecucion_Tarea_triggered()
{
    if (_selectedExecutionIndex.isValid())
    {
        qDebug() << _selectedExecutionIndex.row();
        if (_executionModel->canBeSplitted(_selectedExecutionIndex))
        {
            _executionModel->splitTask(_selectedExecutionIndex);
        }
    }
}
