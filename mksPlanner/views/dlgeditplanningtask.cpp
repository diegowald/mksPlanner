#include "dlgeditplanningtask.h"
#include "ui_dlgeditplanningtask.h"
#include "globalcontainer.h"
#include "models/planningtask.h"
#include "models/proveedor.h"
#include "models/material.h"
#include <QDebug>
#include "views/tablewindow.h"
#include "models/planningtaskmodelconstraint.h"


DlgEditPlanningTask::DlgEditPlanningTask(PlanningTaskModel* model, EntityBasePtr entity, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgEditPlanningTask)
{
    _proveedorByRubroFilterModel = NULL;
    ui->setupUi(this);
    fillTaskTypes();

    _model = model;
    _entity = entity;
    PlanningTaskPtr p = qSharedPointerDynamicCast<PlanningTask>(_entity);


    ui->txtNombre->setText(p->name());
    ui->txtCantidad->setText(QString::number(p->cantidad()));

    ModelBase *m = GlobalContainer::instance().library()->model(Tables::Tareas);
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

    // Por el momento quitamos esto
    ui->lblTareaPadre->setVisible(false);
    ui->cboTareaPadre->setVisible(false);

    TableWindow *t = new TableWindow("", this);
    PlanningTaskModelConstraint *mc = dynamic_cast<PlanningTaskModelConstraint*>(GlobalContainer::instance().projectLibrary(_model->idProyecto())->model(Tables::PlanningTasksConstraints));
    _constraintsFiltered = new PlanningTaskModelConstraintFiltered(_model->idProyecto(), entity->id(), mc);
    t->setModel(_constraintsFiltered);
    t->hideColumn(1);
    //t->hideColumn(2);
    ui->frame->layout()->addWidget(t->window());

}

DlgEditPlanningTask::~DlgEditPlanningTask()
{
    delete ui;
    _materialFilterModel->deleteLater();
    _proveedorByRubroFilterModel->deleteLater();
}

void DlgEditPlanningTask::on_buttonBox_accepted()
{
    PlanningTaskPtr p = qSharedPointerDynamicCast<PlanningTask>(_entity);
    ProveedorPtr prov = qSharedPointerDynamicCast<Proveedor>(GlobalContainer::instance().library()->model(Tables::Proveedores)->getItemByRowid(ui->cboProveedor->currentIndex()));
    p->setIdProveedor(prov.isNull() ? -1 : prov->id());

    MaterialPtr mat = qSharedPointerDynamicCast<Material>(GlobalContainer::instance().library()->model(Tables::Tareas)->getItemByRowid(ui->cboTarea->currentIndex()));
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

int DlgEditPlanningTask::idRubroMaterialSeleccionado()
{
    qDebug() << ui->cboTarea->currentIndex();
    MaterialPtr mat = qSharedPointerDynamicCast<Material>(GlobalContainer::instance().library()->model(Tables::Tareas)->getItemByRowid(ui->cboTarea->currentIndex()));
    return mat.isNull() ? -1 : mat->idRubro();
}

void DlgEditPlanningTask::on_cboTarea_currentIndexChanged(int index)
{
    if (_proveedorByRubroFilterModel != NULL)
    {
        _proveedorByRubroFilterModel->setIdRubro(idRubroMaterialSeleccionado());
    }
}

void DlgEditPlanningTask::fillTaskTypes()
{
    ui->cboTaskType->addItem("Evento", KDGantt::TypeEvent);
    ui->cboTaskType->addItem("Tarea", KDGantt::TypeTask);
    ui->cboTaskType->addItem("Resumen", KDGantt::TypeSummary);
    ui->cboTaskType->addItem("Multiple", KDGantt::TypeMulti);
}
