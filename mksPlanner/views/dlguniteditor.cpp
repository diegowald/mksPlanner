#include "dlguniteditor.h"
#include "ui_dlguniteditor.h"

dlgUnitEditor::dlgUnitEditor(UnitsModel *model, int selectedEntity, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgUnitEditor)
{
    _model = model;
    ui->setupUi(this);
    _mapper = new QDataWidgetMapper(this);
    _mapper->setModel(_model);
    _mapper->addMapping(ui->txtNombre, 0);
    _mapper->addMapping(ui->txtDescripcion, 1);
    _mapper->setCurrentIndex(selectedEntity);
    _mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
}

dlgUnitEditor::~dlgUnitEditor()
{
    delete ui;
}

void dlgUnitEditor::on_buttonBox_accepted()
{
    _mapper->submit();
    close();
}