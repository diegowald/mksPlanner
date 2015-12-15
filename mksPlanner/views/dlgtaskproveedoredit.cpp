#include "dlgtaskproveedoredit.h"
#include "ui_dlgtaskproveedoredit.h"

#include "globalcontainer.h"
#include "models/taskproveedor.h"
#include "models/material.h"

dlgTaskProveedorEdit::dlgTaskProveedorEdit(int idProveedor, TareasProveedoresModel *model, int selectedEntity, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgTaskProveedorEdit)
{
    ui->setupUi(this);
    _model = model;
    ui->cboTarea->setModel(GlobalContainer::instance().materialLibrary()->model(Tables::Tareas));
    ui->cboTarea->setModelColumn(1);

    _entity = _model->getItemByRowid(selectedEntity);

    TaskProveedorPtr tareaProveedor = qSharedPointerDynamicCast<TaskProveedor>(_entity);
    if (!tareaProveedor.isNull())
    {
        MaterialPtr tarea = qSharedPointerDynamicCast<Material>(tareaProveedor->task());
        if (!tarea.isNull())
        {
            ui->cboTarea->setCurrentIndex(ui->cboTarea->findText(tarea->name()));
        }
    }
}

dlgTaskProveedorEdit::~dlgTaskProveedorEdit()
{
    delete ui;
}

void dlgTaskProveedorEdit::on_buttonBox_accepted()
{
    TaskProveedorPtr tareaProveedor = qSharedPointerDynamicCast<TaskProveedor>(_entity);
    MaterialPtr tarea = qSharedPointerDynamicCast<Material>(GlobalContainer::instance().materialLibrary()->model(Tables::Tareas)->getItemByRowid(ui->cboTarea->currentIndex()));
    tareaProveedor->setIdTask(!tarea.isNull() ? tarea->id() : -1);
    _model->setModified();
    close();
}
