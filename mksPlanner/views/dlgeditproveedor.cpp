#include "dlgeditproveedor.h"
#include "ui_dlgeditproveedor.h"
#include <QDebug>

#include "globalcontainer.h"
#include "persistance/materialslibrary.h"
#include "views/tablewindow.h"
#include "models/rubrosproveedoresmodel.h"
#include <QListView>
#include "models/proveedor.h"

dlgEditProveedor::dlgEditProveedor(ProveedoresModel *model, int row, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgEditProveedor)
{
    ui->setupUi(this);

    _model = model;

    _entity = _model->getItemByRowid(row);
    ProveedorPtr prov = qSharedPointerDynamicCast<Proveedor>(_entity);
    ui->txtNombre->setText(prov->name());
    ui->txtContacto->setText(prov->contacto());
    ui->txtEmail->setText(prov->email());
    ui->txtTelefono->setText(prov->telefono());
    ui->txtDireccion->setText(prov->direccion());


    TableWindow *t = new TableWindow("", this);
    dynamic_cast<RubrosProveedoresModel*>(GlobalContainer::instance().library()->model(Tables::RubrosProveedores))->setIdProveedor(_entity->id());
    t->setModel(GlobalContainer::instance().library()->model(Tables::RubrosProveedores));
    t->hideColumn(1);
    t->hideColumn(2);

    ui->frmRubros->layout()->addWidget(t->window());

}

dlgEditProveedor::~dlgEditProveedor()
{
    delete ui;
}

void dlgEditProveedor::on_buttonBox_accepted()
{
    ProveedorPtr prov = qSharedPointerDynamicCast<Proveedor>(_entity);
    prov->setName(ui->txtNombre->text());
    prov->setContacto(ui->txtContacto->text());
    prov->setEMail(ui->txtEmail->text());
    prov->setTelefono(ui->txtTelefono->text());
    prov->setDireccion(ui->txtDireccion->text());

    close();
}
