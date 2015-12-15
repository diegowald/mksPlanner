#include "dlgeditproveedor.h"
#include "ui_dlgeditproveedor.h"
#include <QDebug>

#include "globalcontainer.h"
#include "persistance/materialslibrary.h"
#include "views/tablewindow.h"
#include "models/componentesmateriales.h"

dlgEditProveedor::dlgEditProveedor(ProveedoresModel *model, int row, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgEditProveedor)
{
    ui->setupUi(this);

    _model = model;
    _mapper = new QDataWidgetMapper(this);
    _mapper->setModel(_model);
    _mapper->addMapping(ui->txtNombre, 1);
    _mapper->addMapping(ui->txtTelefono, 2);
    _mapper->setCurrentIndex(row);
    _mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

    TableWindow *t = new TableWindow(this);
    //QWidget* w = QWidget::createWindowContainer(t->window(), this);
    EntityBasePtr entity = _model->getItemByRowid(row);
//    dynamic_cast<ComponentesMaterialesModel*>(GlobalContainer::instance().materialLibrary()->model(Tables::ComponentesMateriales))->setIdMaterialPadre(entity->id());
//    t->setModel(GlobalContainer::instance().materialLibrary()->model(Tables::ComponentesMateriales));

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
