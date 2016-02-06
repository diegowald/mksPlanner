#include "dlgeditplanningtask.h"
#include "ui_dlgeditplanningtask.h"
#include "globalcontainer.h"
#include "models/planningtask.h"
#include "models/proveedor.h"
#include "models/material.h"

DlgEditPlanningTask::DlgEditPlanningTask(PlanningTaskModel* model, int selectedEntity, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgEditPlanningTask)
{
    ui->setupUi(this);

    _model = model;
    _mapper = new QDataWidgetMapper(this);
    _mapper->setModel(_model);

    _mapper->addMapping(ui->txtNombre, model->columnIndex("name"));
    _mapper->addMapping(ui->txtCantidad, model->columnIndex("Cantidad"));

    _mapper->setCurrentIndex(selectedEntity);
    _mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

    ModelBase *m = GlobalContainer::instance().library()->model(Tables::Proveedores);
    ui->cboProveedor->setModel(m);
    ui->cboProveedor->setModelColumn(m->columnIndex("Nombre"));

    m = GlobalContainer::instance().library()->model(Tables::Tareas);
    ui->cboTarea->setModel(m);
    ui->cboTarea->setModelColumn(m->columnIndex("Nombre"));

    _entity = _model->getItemByRowid(selectedEntity);
    PlanningTaskPtr p = qSharedPointerDynamicCast<PlanningTask>(_entity);
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
    /*
     *     setField(1, "idTareaPadre");
    setField(2, "idMaterialTask");
    setField(3, "idProveedor");
    setField(4, "tareaPadre");
    setField(5, "name");
    setField(6, "Rubro");
    setField(7, "materialTask");
    setField(8, "Proveedor");
    setField(9, "Cantidad");
    setField(10, "Fecha Estimada Inicio");
    setField(11, "Fecha Estimada de Finalización");
    setField(12, "Duración");
    setField(13, "Costo");
    setField(14, "Precio");*/
}

DlgEditPlanningTask::~DlgEditPlanningTask()
{
    delete ui;
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
