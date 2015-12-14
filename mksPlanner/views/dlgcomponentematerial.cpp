#include "dlgcomponentematerial.h"
#include "ui_dlgcomponentematerial.h"

#include "globalcontainer.h"
#include "models/material.h"
#include "models/unit.h"
#include "models/componentematerial.h"
#include "models/material.h"
#include "models/unit.h"

dlgComponenteMaterial::dlgComponenteMaterial(int idMaterialPadre, ComponentesMaterialesModel *model, int row, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgComponenteMaterial)
{
    ui->setupUi(this);
    ui->cboMaterial->setModel(GlobalContainer::instance().materialLibrary()->model(Tables::Materiales));
    ui->cboMaterial->setModelColumn(1);
    _model = model;

    _entity = _model->getItemByRowid(row);

    ui->lblmaterialDecripcion->setText("");
    ui->lblUnidadMedida->setText("");
    ui->txtCantidad->setText("");

    ComponenteMaterialPtr componente = qSharedPointerDynamicCast<ComponenteMaterial>(_entity);
    if (!componente.isNull())
    {
        ui->txtCantidad->setText(QString::number(componente->cantidad()));
        if (!componente.isNull())
        {
            MaterialPtr material = qSharedPointerDynamicCast<Material>(componente->material());
            if (!material.isNull())
            {
                ui->cboMaterial->setCurrentIndex(ui->cboMaterial->findText(material->name()));
                ui->lblmaterialDecripcion->setText(material->desription());
                UnitPtr unidad = qSharedPointerDynamicCast<Unit>(material->unit());
                if (!unidad.isNull())
                {
                    ui->lblUnidadMedida->setText(unidad->name());
                }
            }
        }
    }
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
    ComponenteMaterialPtr componente = qSharedPointerDynamicCast<ComponenteMaterial>(_entity);
    MaterialPtr material = qSharedPointerDynamicCast<Material>(GlobalContainer::instance().materialLibrary()->model(Tables::Materiales)->getItemByRowid(ui->cboMaterial->currentIndex()));
    componente->setIdMaterial(!material.isNull() ? material->id() : -1);
    componente->setCantidad(ui->txtCantidad->text().toDouble());
    _model->setModified();
    close();
}

void dlgComponenteMaterial::on_cboMaterial_currentIndexChanged(int index)
{
    QString materialDescription = "";
    QString unidad = "";
    EntityBasePtr entity = GlobalContainer::instance().materialLibrary()->model(Tables::Materiales)->getItemByRowid(ui->cboMaterial->currentIndex());
    if (!entity.isNull())
    {
        MaterialPtr material = qSharedPointerDynamicCast<Material>(entity);
        if (!material.isNull())
        {
            materialDescription = material->desription();
            UnitPtr unit = qSharedPointerDynamicCast<Unit>(material->unit());
            if (!unit.isNull())
            {
                unidad = unit->name();
            }
        }
    }
    ui->lblmaterialDecripcion->setText(materialDescription);
    ui->lblUnidadMedida->setText(unidad);
}
