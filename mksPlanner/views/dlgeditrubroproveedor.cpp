#include "dlgeditrubroproveedor.h"
#include "ui_dlgeditrubroproveedor.h"
#include "globalcontainer.h"
#include "models/entitybase.h"
#include "models/rubroroveedor.h"
#include "models/rubro.h"

DlgEditRubroProveedor::DlgEditRubroProveedor(int idProveedor, RubrosProveedoresModel *model, int selectedEntity, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgEditRubroProveedor)
{
    ui->setupUi(this);
    _model = model;
    ui->cboRubro->clear();
    ui->cboRubro->setModel(GlobalContainer::instance().library()->model(Tables::Rubros));
    ui->cboRubro->setModelColumn(1);

    _entity = _model->getItemByRowid(selectedEntity);

    RubroProveedorPtr rubroProveedor = qSharedPointerDynamicCast<RubroProveedor>(_entity);
    if (!rubroProveedor.isNull())
    {
        RubroPtr rubro = qSharedPointerDynamicCast<Rubro>(rubroProveedor->rubro());
        if (!rubro.isNull())
        {
            ui->cboRubro->setCurrentIndex(ui->cboRubro->findText(rubro->name()));
        }
    }
}

DlgEditRubroProveedor::~DlgEditRubroProveedor()
{
    delete ui;
}

void DlgEditRubroProveedor::on_buttonBox_accepted()
{
    RubroProveedorPtr rubroProveedor = qSharedPointerDynamicCast<RubroProveedor>(_entity);
    RubroPtr rubro = qSharedPointerDynamicCast<Rubro>(GlobalContainer::instance().library()->model(Tables::Rubros)->getItemByRowid(ui->cboRubro->currentIndex()));
    rubroProveedor->setIdRubro(!rubro.isNull() ? rubro->id() : -1);
    _model->setModified();
    close();
}
