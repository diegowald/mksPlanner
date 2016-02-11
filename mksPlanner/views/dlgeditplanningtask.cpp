#include "dlgeditplanningtask.h"
#include "ui_dlgeditplanningtask.h"
#include "globalcontainer.h"
#include "models/planningtask.h"
#include "models/proveedor.h"
#include "models/material.h"
#include <QDebug>



DlgEditPlanningTask::DlgEditPlanningTask(PlanningTaskModel* model, int selectedEntity, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgEditPlanningTask)
{
    _proveedorByRubroFilterModel = NULL;
    ui->setupUi(this);

    _model = model;
    _entity = _model->getItemByRowid(selectedEntity);
    PlanningTaskPtr p = qSharedPointerDynamicCast<PlanningTask>(_entity);


    _mapper = new QDataWidgetMapper(this);
    _mapper->setModel(_model);

    _mapper->addMapping(ui->txtNombre, model->columnIndex("name"));
    _mapper->addMapping(ui->txtCantidad, model->columnIndex("Cantidad"));

    _mapper->setCurrentIndex(selectedEntity);
    _mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

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
    }
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

    _mapper->submit();
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
