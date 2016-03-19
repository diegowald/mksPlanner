#include "dlgeditexecutiontask.h"
#include "ui_dlgeditexecutiontask.h"
#include "globalcontainer.h"
#include "models/executiontask.h"
#include "models/proveedor.h"
#include "models/material.h"
#include "views/tablewindow.h"
#include "models/executiontaskmodelconstraint.h"

DlgEditExecutionTask::DlgEditExecutionTask(ExecutionTaskModel* model, EntityBasePtr entity, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgEditExecutionTask)
{
    _proveedorByRubroFilterModel = NULL;
    ui->setupUi(this);
    fillTaskTypes();

    _model = model;
    _entity = entity;
    ExecutionTaskPtr p = qSharedPointerDynamicCast<ExecutionTask>(_entity);


    ui->txtNombre->setText(p->name());
    ui->txtCantidad->setText(QString::number(p->cantidad()));

    IModel *m = GlobalContainer::instance().library()->model(Tables::Tareas);
    _materialFilterModel = new MaterialFilterModel(m, true, this);
    ui->cboTarea->setModel(_materialFilterModel);
    ui->cboTarea->setModelColumn(m->columnIndex("Nombre"));

    m = GlobalContainer::instance().library()->model(Tables::Proveedores);
    _proveedorByRubroFilterModel = new ProveedorByRubroFilterModel(m, idRubroMaterialSeleccionado(), this);
    ui->cboProveedor->setModel(_proveedorByRubroFilterModel);
    ui->cboProveedor->setModelColumn(m->columnIndex("Nombre"));


    if (!p.isNull())
    {
        if (p->idProveedor() != -1)
        {
            ProveedorPtr prov = qSharedPointerDynamicCast<Proveedor>(p->proveedor());
            ui->cboProveedor->setCurrentIndex(ui->cboProveedor->findText(prov->name()));
        }
        if (p->idMaterialTask() != -1)
        {
            MaterialPtr m = qSharedPointerDynamicCast<Material>(p->materialTask());
            ui->cboTarea->setCurrentIndex(ui->cboTarea->findText(m->name()));
        }
        ui->dateFechaEstimadaInicio->setDateTime(p->fechaEstimadaInicio());
        ui->dateFechaEstimadaFinalizacion->setDateTime(p->fechaEstimadaFin());
        ui->cboTaskType->setCurrentIndex(ui->cboTaskType->findData(static_cast<int>(p->taskType())));
    }

    TableWindow *t = new TableWindow("", this);
    ExecutionTaskModelConstraint *mc = dynamic_cast<ExecutionTaskModelConstraint*>(GlobalContainer::instance().projectLibrary(_model->idProyecto())->model(Tables::ExecutionTasksConstraints));
    _constraintsFiltered = new ExecutionTaskModelConstraintFiltered(_model->idProyecto(), entity->id(), mc);
    t->setModel(_constraintsFiltered);
    t->hideColumn(1);
    t->hideColumn(2);
    t->hideColumn(3);
    t->hideColumn(4);
    ui->frame->layout()->addWidget(t->window());

}

DlgEditExecutionTask::~DlgEditExecutionTask()
{
    delete ui;
    _materialFilterModel->deleteLater();
    _proveedorByRubroFilterModel->deleteLater();
}

void DlgEditExecutionTask::on_buttonBox_accepted()
{
    ExecutionTaskPtr p = qSharedPointerDynamicCast<ExecutionTask>(_entity);
    ProveedorPtr prov = qSharedPointerDynamicCast<Proveedor>(GlobalContainer::instance().library()->model(Tables::Proveedores)->getItemByRowid(ui->cboProveedor->currentIndex()));
    p->setIdProveedor(prov.isNull() ? -1 : prov->id());

    MaterialPtr mat = qSharedPointerDynamicCast<Material>(_materialFilterModel->getItemByRowid(ui->cboTarea->currentIndex()));
    p->setIdMaterialTask(mat.isNull() ? -1 : mat->id());

    QDateTime dt = ui->dateFechaEstimadaInicio->dateTime();
    p->setFechaEstimadaInicio(dt);
    dt = ui->dateFechaEstimadaFinalizacion->dateTime();
    p->setFechaEstimadaFin(dt);

    p->setCantidad(ui->txtCantidad->text().toDouble());
    p->setName(ui->txtNombre->text());

    p->setTaskType(static_cast<KDGantt::ItemType>(ui->cboTaskType->currentData(Qt::UserRole).toInt()));

    close();
}

int DlgEditExecutionTask::idRubroMaterialSeleccionado()
{
    qDebug() << ui->cboTarea->currentIndex();
    MaterialPtr mat = qSharedPointerDynamicCast<Material>(GlobalContainer::instance().library()->model(Tables::Tareas)->getItemByRowid(ui->cboTarea->currentIndex()));
    return mat.isNull() ? -1 : mat->idRubro();
}

void DlgEditExecutionTask::on_cboTarea_currentIndexChanged(int)
{
    if (_proveedorByRubroFilterModel != NULL)
    {
        _proveedorByRubroFilterModel->setIdRubro(idRubroMaterialSeleccionado());
    }
}

void DlgEditExecutionTask::fillTaskTypes()
{
    ui->cboTaskType->addItem("Evento", KDGantt::TypeEvent);
    ui->cboTaskType->addItem("Tarea", KDGantt::TypeTask);
    ui->cboTaskType->addItem("Resumen", KDGantt::TypeSummary);
    ui->cboTaskType->addItem("Multiple", KDGantt::TypeMulti);
}

void DlgEditExecutionTask::on_cboTaskType_currentIndexChanged(int)
{
    bool enable = true;
    switch (ui->cboTaskType->currentData(Qt::UserRole).toInt())
    {
    case KDGantt::TypeTask:
        enable = true;
        break;
    case KDGantt::TypeEvent:
    case KDGantt::TypeSummary:
    case KDGantt::TypeMulti:
    default:
        enable = false;
    }
    ui->cboProveedor->setEnabled(enable);
    ui->cboTarea->setEnabled(enable);
    ui->txtCantidad->setEnabled(enable);
    ui->dateFechaEstimadaFinalizacion->setEnabled(enable);
    ui->dateFechaEstimadaInicio->setEnabled(enable);
    ui->frame->setEnabled(enable);
}
