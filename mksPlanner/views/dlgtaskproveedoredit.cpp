#include "dlgtaskproveedoredit.h"
#include "ui_dlgtaskproveedoredit.h"

dlgTaskProveedorEdit::dlgTaskProveedorEdit(TareasProveedoresModel *model, int selectedEntity, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgTaskProveedorEdit)
{
    ui->setupUi(this);
    _model = model;
    ui->setupUi(this);
    _mapper = new QDataWidgetMapper(this);
    _mapper->setModel(_model);
/*    _mapper->addMapping(ui->txtNombre, 0);
    _mapper->addMapping(ui->txtDescripcion, 1);*/
    _mapper->setCurrentIndex(selectedEntity);
    _mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
}

dlgTaskProveedorEdit::~dlgTaskProveedorEdit()
{
    delete ui;
}

void dlgTaskProveedorEdit::on_buttonBox_accepted()
{
    _mapper->submit();
    close();
}
