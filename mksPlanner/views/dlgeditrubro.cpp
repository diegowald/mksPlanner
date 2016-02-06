#include "dlgeditrubro.h"
#include "ui_dlgeditrubro.h"
#include "models/rubro.h"



DlgEditRubro::DlgEditRubro(RubrosModel *model, int selectedEntity, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgEditRubro)
{
    _model = model;
    ui->setupUi(this);
    _mapper = new QDataWidgetMapper(this);
    _mapper->setModel(_model);
    _mapper->addMapping(ui->txtNombre, model->columnIndex("Nombre"));
    _mapper->addMapping(ui->txtDescripcion, model->columnIndex("Descripción"));

    _entity = model->getItemByRowid(selectedEntity);
    RubroPtr rubro = qSharedPointerDynamicCast<Rubro>(_entity);
    ui->chkRubroTareas->setChecked(rubro->isTask());

    _mapper->setCurrentIndex(selectedEntity);
    _mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
}

DlgEditRubro::~DlgEditRubro()
{
    delete ui;
}

void DlgEditRubro::on_buttonBox_accepted()
{
    RubroPtr rubro = qSharedPointerDynamicCast<Rubro>(_entity);
    rubro->setIsTask(ui->chkRubroTareas->isChecked());

    _mapper->submit();
    close();
}
