#include "dlgeditproveedor.h"
#include "ui_dlgeditproveedor.h"
#include <QDebug>

#include "globalcontainer.h"
#include "persistance/materialslibrary.h"
#include "views/tablewindow.h"
#include "models/tareasproveedoresmodel.h"

dlgEditProveedor::dlgEditProveedor(ProveedoresModel *model, int row, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgEditProveedor)
{
    ui->setupUi(this);

    _model = model;
    _mapper = new QDataWidgetMapper(this);
    _mapper->setModel(_model);
    _mapper->addMapping(ui->txtNombre, 1);
    _mapper->addMapping(ui->txtContacto, 2);
    _mapper->addMapping(ui->txtEmail, 3);
    _mapper->addMapping(ui->txtTelefono, 4);
    _mapper->addMapping(ui->txtDireccion, 5);

    _mapper->setCurrentIndex(row);
    _mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

    TableWindow *t = new TableWindow("", this);
    EntityBasePtr entity = _model->getItemByRowid(row);
    dynamic_cast<TareasProveedoresModel*>(GlobalContainer::instance().materialLibrary()->model(Tables::TareasProveedores))->setIdProveedor(entity->id());
    t->setModel(GlobalContainer::instance().materialLibrary()->model(Tables::TareasProveedores));

    ui->frame->layout()->addWidget(t->window());
}

dlgEditProveedor::~dlgEditProveedor()
{
    delete ui;
}

void dlgEditProveedor::on_buttonBox_accepted()
{
    _mapper->submit();
    close();
}
