#include "dlguniteditor.h"
#include "ui_dlguniteditor.h"
#include "models/unit.h"


dlgUnitEditor::dlgUnitEditor(UnitsModel *model, int selectedEntity, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgUnitEditor)
{
    _model = model;
    ui->setupUi(this);

    _entity = model->getItemByRowid(selectedEntity);
    UnitPtr unit = qSharedPointerDynamicCast<Unit>(_entity);
    ui->txtNombre->setText(unit->name());
    ui->txtDescripcion->setText(unit->description());
}

dlgUnitEditor::~dlgUnitEditor()
{
    delete ui;
}

void dlgUnitEditor::on_buttonBox_accepted()
{
    UnitPtr unit = qSharedPointerDynamicCast<Unit>(_entity);
    unit->setName(ui->txtNombre->text());
    unit->setDescripcion(ui->txtDescripcion->text());

    close();
}
