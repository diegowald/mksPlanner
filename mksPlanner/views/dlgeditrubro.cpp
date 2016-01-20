#include "dlgeditrubro.h"
#include "ui_dlgeditrubro.h"

DlgEditRubro::DlgEditRubro(RubrosModel *model, int selectedEntity, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgEditRubro)
{
    _model = model;
    ui->setupUi(this);
    _mapper = new QDataWidgetMapper(this);
    _mapper->setModel(_model);
    _mapper->addMapping(ui->txtNombre, 1);
    _mapper->addMapping(ui->txtDescripcion, 2);
    _mapper->setCurrentIndex(selectedEntity);
    _mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
}

DlgEditRubro::~DlgEditRubro()
{
    delete ui;
}

void DlgEditRubro::on_buttonBox_accepted()
{
    _mapper->submit();
    close();
}
