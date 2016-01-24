#include "dlgcomponentematerial.h"
#include "ui_dlgcomponentematerial.h"

#include "globalcontainer.h"
#include "models/material.h"
#include "models/unit.h"
#include "models/componentematerial.h"
#include "models/material.h"
#include "models/unit.h"

#include <QDebug>

dlgComponenteMaterial::dlgComponenteMaterial(int idMaterialPadre, ComponentesMaterialesModel *model, int row, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgComponenteMaterial)
{
    // Aca hay que quitar el filtro
    _materialsModel = new ValidMaterialFilterModel(idMaterialPadre,
                                                   GlobalContainer::instance().materialLibrary()->model(Tables::Materiales),
                                                   this);

    ui->setupUi(this);

    ui->cboMaterial->setModel(_materialsModel);
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
                qDebug() << ui->cboMaterial->count();
                ui->cboMaterial->setCurrentIndex(ui->cboMaterial->findText(material->name()));
                ui->lblmaterialDecripcion->setText(material->description());
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


void dlgComponenteMaterial::on_buttonBox_accepted()
{
    ComponenteMaterialPtr componente = qSharedPointerDynamicCast<ComponenteMaterial>(_entity);
    MaterialPtr material = qSharedPointerDynamicCast<Material>(_materialsModel->getItemByRowid(ui->cboMaterial->currentIndex()));
    componente->setIdMaterial(!material.isNull() ? material->id() : -1);
    componente->setCantidad(ui->txtCantidad->text().toDouble());
    _model->setModified();
    close();
}

void dlgComponenteMaterial::on_cboMaterial_currentIndexChanged(int index)
{
    qDebug() << ui->cboMaterial->count();
    QString materialDescription = "";
    QString unidad = "";
    EntityBasePtr entity = _materialsModel->getItemByRowid(ui->cboMaterial->currentIndex());
    if (!entity.isNull())
    {
        MaterialPtr material = qSharedPointerDynamicCast<Material>(entity);
        if (!material.isNull())
        {
            materialDescription = material->description();
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
