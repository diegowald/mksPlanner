#include "projectwindow.h"
#include "ui_projectwindow.h"
#include <QTreeView>
#include "models/proyectomodel.h"
#include "globalcontainer.h"
#include "models/planningtask.h"
#include "models/proyecto.h"
#include "models/proveedor.h"
#include "models/tareacertificadosmodel.h"
#include "models/tareascertificado.h"
#include <QSet>
#include "views/dlgeditfechapagocertificado.h"
#include "views/executiontaskitemdelegate.h"

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

    _execConstraintModel = NULL;
    _certificacionesModel = NULL;
    _tareasCertificacionEnProceso = NULL;
    _tareasCertificadoEnProceso = NULL;
    _certificadosEnProceso = NULL;

    _certificadosHechosModel = NULL;
    _tareasCertificadoHechosModel = NULL;

    _certificadoMapper = NULL;

    //_idInterno = -1;

    _idCertificacionSeleccionada = -1;
    _idProveedorSeleccionado = -1;
    ui->executionView->setItemDelegate(new ExecutionTaskItemDelegate(_executionModel, this));
}

ProjectWindow::~ProjectWindow()
{
    delete ui;
}

void ProjectWindow::setProjectLibrary(ProjectLibrary *library)
{
    _projectLibrary = library;
    setModel(_projectLibrary->model(Tables::Proyectos));
    setPlanningModel(_projectLibrary->model(Tables::PlanningTasks));
    setConstraintModel(_projectLibrary->model(Tables::PlanningTasksConstraints));
    setExecutionModel(_projectLibrary->model(Tables::ExecutionTasks));
    setExecutionConstraintModel(_projectLibrary->model(Tables::ExecutionTasksConstraints));
    setCertificacionesModel(_projectLibrary->model(Tables::Certificaciones));
    updateBotonesEstados();
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
    ui->executionView->setItemDelegate(new ExecutionTaskItemDelegate(_executionModel, this));
}

void ProjectWindow::setExecutionConstraintModel(IModel *model)
{
    _execConstraintModel = new ExecutionTaskModelConstraintAdapter(_executionModel, model, this);
    ui->executionView->setConstraintModel(_execConstraintModel);
}

void ProjectWindow::setCertificacionesModel(IModel *model)
{
    _certificacionesModel = dynamic_cast<CertificacionesModel*>(model);
    ui->tblCertificaciones->setModel(_certificacionesModel);
    ui->tblCertificaciones->setColumnHidden(0, true);

    connect(ui->tblCertificaciones->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, &ProjectWindow::on_tblCertificaciones_selectionChanged);

    _tareasCertificacionEnProceso = new ModelFilter(_executionModel->innerModel(),
                                                    [&] (EntityBasePtr e) -> bool
    {
            ExecutionTaskPtr ex = qSharedPointerDynamicCast<ExecutionTask>(e);
            return ex->idCertificacion() == _idCertificacionSeleccionada;
}, this);

    _tareasCertificadoEnProceso = new ModelFilter(_tareasCertificacionEnProceso,
                                                  [&] (EntityBasePtr e) -> bool
    {
            ExecutionTaskPtr ex = qSharedPointerDynamicCast<ExecutionTask>(e);
            return (ex->idCertificacion() == _idCertificacionSeleccionada)
            && ((ex->idProveedor() == _idProveedorSeleccionado) || (_idProveedorSeleccionado == -2));
});

    _certificadosEnProceso = new ModelFilter(GlobalContainer::instance().library()->model(Tables::Proveedores),
                                             [&] (EntityBasePtr e) -> bool
    {
            QSet<int> idsProveedores;
            foreach (int id, _tareasCertificacionEnProceso->ids())
    {
            EntityBasePtr t = _tareasCertificacionEnProceso->getItem(id);
            ExecutionTaskPtr et = qSharedPointerDynamicCast<ExecutionTask>(t);
            idsProveedores.insert(et->idProveedor());
}

            return idsProveedores.contains(e->id());
});

    _certificadosHechosModel = new ModelFilter(_projectLibrary->model(Tables::Certificados),
                                               [&] (EntityBasePtr e) -> bool
    {
            CertificadoPtr c = qSharedPointerDynamicCast<Certificado>(e);
            return c->idCertificacion() == _idCertificacionSeleccionada;
});

    _tareasCertificadoHechosModel = new ModelFilter(_projectLibrary->model(Tables::TareaCertificados),
                                                    [&] (EntityBasePtr e) -> bool
    {
            TareaCertificadoPtr c = qSharedPointerDynamicCast<TareaCertificado>(e);
            return (c->idCertificacion() == _idCertificacionSeleccionada)
            && (c->idProveedor() == _idProveedorSeleccionado);
});
    updateCertificacionView(EntityBasePtr());
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
    }
}

void ProjectWindow::on_actionEdit_Task_triggered()
{
    QModelIndex index = ui->planningView->selectionModel()->currentIndex();
    _planningModel->editEntity(index);
    _certificacionesModel->refreshData();
    _tareasCertificacionEnProceso->refreshData();
}

void ProjectWindow::on_actionRemove_Task_triggered()
{
    QModelIndex index = ui->planningView->selectionModel()->currentIndex();
    _planningModel->removeEntity(window(), index);
}

void ProjectWindow::on_actionGuardar_cambios_triggered()
{
    _projectLibrary->save();
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
    {
        _executionModel->editEntity(index);
        _certificacionesModel->refreshData();
        _certificadosEnProceso->refreshData();
        _certificadosHechosModel->refreshData();
        _tareasCertificacionEnProceso->refreshData();
        _tareasCertificadoEnProceso->refreshData();
        _tareasCertificadoHechosModel->refreshData();
    }
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

void ProjectWindow::on_actionNueva_Certificacion_triggered()
{
    int rowCount = ui->tblCertificaciones->model()->rowCount();
    QModelIndex index = ui->tblCertificaciones->selectionModel()->currentIndex();

    if (!_certificacionesModel->insertRow(rowCount, index.parent()))
        return;
    _certificacionesModel->editEntity(rowCount);
}

void ProjectWindow::on_actionEditar_Certificacion_triggered()
{
    QModelIndex index = ui->tblCertificaciones->selectionModel()->currentIndex();
    _certificacionesModel->editEntity(index.row());
}

void ProjectWindow::on_actionBorrar_Ceritificacion_triggered()
{
    QModelIndex index = ui->tblCertificaciones->selectionModel()->currentIndex();
    _certificacionesModel->removeEntity(window(), index);
}

void ProjectWindow::on_tblCertificaciones_selectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
    if ((selected.count() > 0) && (selected.at(0).isValid()))
    {
        EntityBasePtr e = _certificacionesModel->getItemByRowid(selected.at(0).top());
        updateCertificacionView(e);
    }
    else
    {
        updateCertificacionView(EntityBasePtr());
    }
}

void ProjectWindow::on_tblCertificados_selectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
    if ((selected.count() > 0) && (selected.at(0).isValid()))
    {
        EntityBasePtr e = dynamic_cast<IModel*>(ui->tblCertificados->model())->getItemByRowid(selected.at(0).top());
        _idProveedorSeleccionado = e->id();
        _tareasCertificacionEnProceso->refreshData();
        _tareasCertificadoEnProceso->refreshData();
        _tareasCertificadoHechosModel->refreshData();
//        _certificadosEnProceso->refreshData();
//        _tareasCertificadoEnProceso->refreshData();
        ui->btnVerCertificadoClienteEnProceso->setChecked(false);
    }
    else
    {
        ui->btnVerCertificadoClienteEnProceso->setChecked(true);
    }
}

void ProjectWindow::updateCertificacionView(EntityBasePtr certificacion)
{
    if (!certificacion.isNull())
    {
        ui->frmDetalleCertificado->setEnabled(true);
        _idCertificacionSeleccionada = certificacion->id();
        CertificacionPtr c = qSharedPointerDynamicCast<Certificacion>(certificacion);
        switch (c->certificacionStatus())
        {
        case Certificacion::CertificacionStatus::Preparacion:
        {
            ui->tblTareasCertificado->setModel(_tareasCertificadoEnProceso);
            ui->tblCertificados->setModel(_certificadosEnProceso);

            ui->tblCertificados->hideColumn(0);

            ui->tblTareasCertificado->hideColumn(0);
            ui->tblTareasCertificado->hideColumn(1);
            ui->tblTareasCertificado->hideColumn(2);
            ui->tblTareasCertificado->hideColumn(3);

            ui->btnVerCertificadoClienteEnProceso->setVisible(true);

            connect(ui->tblCertificados->selectionModel(), &QItemSelectionModel::selectionChanged,
                    this, &ProjectWindow::on_tblCertificados_selectionChanged);


            _certificadoMapper = new QDataWidgetMapper(this);
            _certificadoMapper->setModel(_projectLibrary->model(Tables::Certificados));

            _certificadoMapper->addMapping(ui->nroCertificado, _certificacionesModel->columnIndex("Nro. Certificado"));
            _certificadoMapper->addMapping(ui->txtCliente, _certificacionesModel->columnIndex("Cliente"));
            _certificadoMapper->addMapping(ui->txtProveedor, _certificacionesModel->columnIndex("Proveedor"));
            _certificadoMapper->addMapping(ui->dateEmision, _certificacionesModel->columnIndex("Fecha Emisión"));
            _certificadoMapper->addMapping(ui->dateDesde, _certificacionesModel->columnIndex("Desde"));
            _certificadoMapper->addMapping(ui->dateHasta, _certificacionesModel->columnIndex("Hasta"));

            _certificadoMapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);
            _tareasCertificacionEnProceso->refreshData();
            _certificadosEnProceso->refreshData();
            ui->btnEmitido->setVisible(true);
            ui->btnAbonado->setVisible(false);
            ui->lblEstadoCertificacion->setText("En Preparación");
        }
            break;
        case Certificacion::CertificacionStatus::Emitido:
        {
            ui->tblCertificados->setModel(_certificadosHechosModel);
            ui->tblTareasCertificado->setModel(_tareasCertificadoHechosModel);
            connect(ui->tblCertificados->selectionModel(), &QItemSelectionModel::selectionChanged,
                    this, &ProjectWindow::on_tblCertificados_selectionChanged);

            ui->tblCertificados->hideColumn(0);
            ui->tblCertificados->hideColumn(1);
            ui->tblCertificados->hideColumn(2);

            ui->tblTareasCertificado->hideColumn(0);
            ui->tblTareasCertificado->hideColumn(1);
            ui->tblTareasCertificado->hideColumn(2);
            ui->tblTareasCertificado->hideColumn(4);

            ui->btnEmitido->setVisible(false);
            ui->btnAbonado->setVisible(true);
            ui->lblEstadoCertificacion->setText("Emitido");

            _certificadoMapper = new QDataWidgetMapper(this);
            _certificadoMapper->setModel(_certificadosHechosModel);

            _certificadoMapper->addMapping(ui->nroCertificado, _certificadosHechosModel->columnIndex("Nro. Certificado"));
            _certificadoMapper->addMapping(ui->txtCliente, _certificadosHechosModel->columnIndex("Cliente"));
            _certificadoMapper->addMapping(ui->txtProveedor, _certificadosHechosModel->columnIndex("Proveedor"));
            _certificadoMapper->addMapping(ui->dateEmision, _certificadosHechosModel->columnIndex("Fecha Emisión"));
            _certificadoMapper->addMapping(ui->dateDesde, _certificadosHechosModel->columnIndex("Desde"));
            _certificadoMapper->addMapping(ui->dateHasta, _certificadosHechosModel->columnIndex("Hasta"));

            _certificadosHechosModel->refreshData();
            _tareasCertificadoHechosModel->refreshData();
            ui->nroCertificado->setEnabled(false);
            ui->txtCliente->setEnabled(true);
            ui->txtProveedor->setReadOnly(true);
            ui->dateEmision->setReadOnly(true);
            ui->dateDesde->setReadOnly(true);
            ui->dateHasta->setReadOnly(true);

            _certificadoMapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);

        }
            break;
        default:
            break;
        }
        recalcularTotalesCertificado(certificacion);
    }
    else
    {
        ui->frmDetalleCertificado->setEnabled(false);
    }

}

void ProjectWindow::recalcularTotalesCertificado(EntityBasePtr certificacion)
{
    double costoTotal = 0.;
    double precioTotal = 0.;
    if (!certificacion.isNull())
    {
        ui->frmDetalleCertificado->setEnabled(true);
        _idCertificacionSeleccionada = certificacion->id();
        CertificacionPtr c = qSharedPointerDynamicCast<Certificacion>(certificacion);
        switch (c->certificacionStatus())
        {
        case Certificacion::CertificacionStatus::Preparacion:
        {
            QSet<int> ids = _tareasCertificacionEnProceso->ids();
            foreach (int id, ids.values())
            {
                EntityBasePtr e = _tareasCertificacionEnProceso->getItem(id);
                ExecutionTaskPtr et = qSharedPointerDynamicCast<ExecutionTask>(e);
                costoTotal += et->costo();
                precioTotal += et->precio();
            }
            break;
        }
        case Certificacion::CertificacionStatus::Emitido:
        {
            QSet<int> ids = _tareasCertificadoHechosModel->ids();
            foreach (int id, ids.values())
            {
                EntityBasePtr e = _tareasCertificadoHechosModel->getItem(id);
                TareaCertificadoPtr tc = qSharedPointerDynamicCast<TareaCertificado>(e);
                ExecutionTaskPtr et = qSharedPointerDynamicCast<ExecutionTask>(tc->tareaEjecucion());
                costoTotal += et->costo();
                precioTotal += et->precio();
            }
            break;
        }
        default:
            break;
        }
        ui->txtCostoTotal->setText(QString::number(costoTotal));
        ui->txtPrecioTotal->setText(QString::number(precioTotal));
        if (_idProveedorSeleccionado == -2)
        {
            ui->txtCostoTotal->setVisible(true);
            ui->txtPrecioTotal->setVisible(false);
        }
        else
        {
            ui->txtCostoTotal->setVisible(false);
            ui->txtPrecioTotal->setVisible(true);
        }
    }
}

void ProjectWindow::on_btnAbonado_released()
{
    dlgEditFechaPagoCertificado dlg(this);
    if (dlg.exec() == QDialog::Accepted)
    {
        CertificadosModel *certModel = static_cast<CertificadosModel*>(_projectLibrary->model(Tables::Certificados));
        EntityBasePtr e =
                certModel->getItemByCertificacionIdProveedorId(
                    _idCertificacionSeleccionada,
                    _idProveedorSeleccionado);
        CertificadoPtr c = certModel->cast(e);
        c->setFechaPago(dlg.fechaPago());
    }
}

void ProjectWindow::certiicarTareasEnEjecucion(EntityBasePtr certificaion)
{
    QSet<int> ids = _tareasCertificacionEnProceso->ids();
    foreach (int id, ids.values())
    {
        ExecutionTaskPtr et = qSharedPointerDynamicCast<ExecutionTask>(_tareasCertificacionEnProceso->getItem(id));

        CertificacionPtr c = qSharedPointerDynamicCast<Certificacion>(certificaion);
        _executionModel->splitTask(et, c->fechaCertificacion());
    }
    _tareasCertificacionEnProceso->refreshData();
}

void ProjectWindow::on_btnEmitido_released()
{
    CertificacionPtr cert = qSharedPointerDynamicCast<Certificacion>(_certificacionesModel->getItem(_idCertificacionSeleccionada));
    cert->setCertificacionStatus(Certificacion::CertificacionStatus::Emitido);

    _tareasCertificacionEnProceso->refreshData();
    certiicarTareasEnEjecucion(cert);

    QSet<int> ids = _tareasCertificacionEnProceso->ids();
    foreach (int id, ids.values())
    {
        ExecutionTaskPtr et = qSharedPointerDynamicCast<ExecutionTask>(_tareasCertificacionEnProceso->getItem(id));
        TareaCertificadoPtr tc = qSharedPointerDynamicCast<TareaCertificado>(
                    _tareasCertificadoHechosModel->createEntity());
        tc->setIdCertificacion(_idCertificacionSeleccionada);
        tc->setIdProveedor(et->idProveedor());
        tc->setIdTareaEjecucion(et->id());
        _tareasCertificadoHechosModel->addEntity(tc);
    }

    _certificadosEnProceso->refreshData();
    ids = _certificadosEnProceso->ids();
    foreach (int id, ids)
    {
        ProveedorPtr p = qSharedPointerDynamicCast<Proveedor>(_certificadosEnProceso->getItem(id));
        CertificadoPtr c = qSharedPointerDynamicCast<Certificado>(_certificadosHechosModel->createEntity());
        c->setIdProveedor(p->id());
        c->setIdCertificacion(_idCertificacionSeleccionada);
        c->setFechaEmision(cert->fechaCertificacion());
        _certificadosHechosModel->addEntity(c);
    }
    updateCertificacionView(cert);
    emit _certificacionesModel->layoutChanged();
    emit _tareasCertificadoHechosModel->layoutChanged();
    emit _certificadosHechosModel->layoutChanged();
}


void ProjectWindow::on_btnVerCertificadoClienteEnProceso_toggled(bool checked)
{
    if (checked)
    {
        ui->tblCertificados->selectionModel()->clearSelection();
        _idProveedorSeleccionado = -2;
        _tareasCertificacionEnProceso->refreshData();
        _tareasCertificadoEnProceso->refreshData();
        _tareasCertificadoHechosModel->refreshData();
    }
}

void ProjectWindow::on_actionAddExecutionSubTask_triggered()
{
    QModelIndex idx = ui->planningView->selectionModel()->currentIndex();
    if (idx.isValid())
    {
        qDebug() << "MainWindow::slotToolsNewItem" << idx;
        if (!_planningModel->insertRow(1, _planningModel->index(idx.row(), 0, idx.parent())))
            return;
    }
}

void ProjectWindow::on_actionAddExecutionTask_triggered()
{
    int rowCount = ui->executionView->model()->rowCount();

    QModelIndex index = ui->executionView->selectionModel()->currentIndex();


    if (!_executionModel->insertRow(rowCount, index.parent()))
        return;

    _executionModel->editEntity(rowCount);
}

void ProjectWindow::on_actionEditExecutionTask_triggered()
{
    QModelIndex index = ui->executionView->selectionModel()->currentIndex();
    _executionModel->editEntity(index);
    _certificacionesModel->refreshData();
    _tareasCertificacionEnProceso->refreshData();
}

void ProjectWindow::on_actionDeleteExecutionTask_triggered()
{
    QModelIndex index = ui->executionView->selectionModel()->currentIndex();
    _executionModel->removeEntity(window(), index);
}
