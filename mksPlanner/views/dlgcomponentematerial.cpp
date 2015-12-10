#include "dlgcomponentematerial.h"
#include "ui_dlgcomponentematerial.h"

#include "globalcontainer.h"

dlgComponenteMaterial::dlgComponenteMaterial(int idMaterialPadre, ComponentesMaterialesModel *model, int row, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgComponenteMaterial)
{
    ui->setupUi(this);
    ui->cboMaterial->setModel(GlobalContainer::instance().materialLibrary()->model("materiales"));
    ui->cboMaterial->setModelColumn(1);
    _model = model;
    _mapper = new QDataWidgetMapper(this);
    _mapper->setModel(_model);
    _mapper->addMapping(ui->cboMaterial, 1, "currentIndex");
    _mapper->addMapping(ui->lblmaterialDecripcion, 1);
    _mapper->addMapping(ui->txtCantidad, 2);
    _mapper->setCurrentIndex(row);
    ui->cboMaterial->setCurrentIndex(idMaterialPadre);
    _mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
}

dlgComponenteMaterial::~dlgComponenteMaterial()
{
    delete ui;
}

/*
void dlgMaterialEditor::on_buttonBox_accepted()
{
    qDebug() << ui->cboUnit->currentData();
    qDebug() << ui->cboUnit->currentIndex();
    qDebug() << ui->cboUnit->currentText();
    _mapper->submit();
    close();
}
*/

void dlgComponenteMaterial::on_buttonBox_accepted()
{
    _mapper->submit();
    close();
}
