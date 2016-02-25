#include "dlgeditrubro.h"
#include "ui_dlgeditrubro.h"
#include "models/rubro.h"



DlgEditRubro::DlgEditRubro(RubrosModel *model, int selectedEntity, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgEditRubro)
{
    _model = model;
    ui->setupUi(this);

    _entity = model->getItemByRowid(selectedEntity);
    RubroPtr rubro = qSharedPointerDynamicCast<Rubro>(_entity);
    ui->txtNombre->setText(rubro->name());
    ui->txtDescripcion->setText(rubro->description());
    ui->chkRubroTareas->setChecked(rubro->isTask());

}

DlgEditRubro::~DlgEditRubro()
{
    delete ui;
}

void DlgEditRubro::on_buttonBox_accepted()
{
    RubroPtr rubro = qSharedPointerDynamicCast<Rubro>(_entity);
    rubro->setIsTask(ui->chkRubroTareas->isChecked());
    rubro->setName(ui->txtNombre->text());
    rubro->setDescripcion(ui->txtDescripcion->text());

    close();
}
