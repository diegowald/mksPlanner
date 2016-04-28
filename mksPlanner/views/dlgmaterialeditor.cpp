#include "dlgmaterialeditor.h"
#include "ui_dlgmaterialeditor.h"
#include "globalcontainer.h"
#include "persistance/materialslibrary.h"
#include "views/tablewindow.h"
#include "models/componentesmateriales.h"
#include "models/unit.h"
#include "models/material.h"
#include "models/rubro.h"
#include "models/modelfilter.h"
#include <QDebug>


dlgMaterialEditor::dlgMaterialEditor(MaterialesBaseModel *model, int row, bool isTask, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgMaterialEditor)
{
    ui->setupUi(this);

    ui->cboUnit->setModel(GlobalContainer::instance().library()->model(Tables::Unidades));

    _isTask = isTask;
    _rubroFilter = new ModelFilter(GlobalContainer::instance().library()->model(Tables::Rubros),
                                   [&] (EntityBasePtr e) -> bool
        {
            RubroPtr r = qSharedPointerDynamicCast<Rubro>(e);
            qDebug() << _isTask << ", " << r->isTask() << ", " << r->name();
            return _isTask ? r->isTask() : !r->isTask();
        }, this);
    //ui->cboRubro->setModel(GlobalContainer::instance().library()->model(Tables::Rubros));
    ui->cboRubro->setModel(_rubroFilter);

    //falta hacer que se vea el nombre de la unidad y que se seleccione el id
    ui->cboUnit->setModelColumn(1);
    ui->cboRubro->setModelColumn(1);

    _model = model;


    _entity = model->getItemByRowid(row);
    MaterialPtr material = qSharedPointerDynamicCast<Material>(_entity);

    ui->txtName->setText(material->name());
    ui->txtDescription->setText(material->description());

    if (material->isTask())
    {
        setWindowTitle("Editar Tarea");
    }
    else
    {
        setWindowTitle("Editar Material");
    }
    UnitPtr unit = qSharedPointerDynamicCast<Unit>(material->unit());
    if (!unit.isNull())
    {
        ui->cboUnit->setCurrentIndex(ui->cboUnit->findText(unit->name()));
    }

    RubroPtr rubro = qSharedPointerDynamicCast<Rubro>(material->rubro());
    if (!rubro.isNull())
    {
        ui->cboRubro->setCurrentIndex(ui->cboRubro->findText(rubro->name()));
    }


    TableWindow *t = new TableWindow("", this);
    _entity = _model->getItemByRowid(row);
    dynamic_cast<ComponentesMaterialesModel*>(GlobalContainer::instance().library()->model(Tables::ComponentesMateriales))->setIdMaterialPadre(_entity->id());
    t->setModel(GlobalContainer::instance().library()->model(Tables::ComponentesMateriales));
    t->hideColumn(1);
    t->hideColumn(2);
    ui->frame->layout()->addWidget(t->window());
}

dlgMaterialEditor::~dlgMaterialEditor()
{
    delete ui;
}

void dlgMaterialEditor::on_buttonBox_accepted()
{
    /*qDebug() << ui->cboUnit->currentData();
    qDebug() << ui->cboUnit->currentIndex();
    qDebug() << ui->cboUnit->currentText();*/

    MaterialPtr material = qSharedPointerDynamicCast<Material>(_entity);
    EntityBasePtr entity = GlobalContainer::instance().library()->model(Tables::Unidades)->getItemByRowid(ui->cboUnit->currentIndex());
    if (!entity.isNull())
    {
        UnitPtr unit = qSharedPointerDynamicCast<Unit>(entity);
        material->setUnit(unit->id());
    }

    entity = GlobalContainer::instance().library()->model(Tables::Rubros)->getItemByRowid(ui->cboRubro->currentIndex());
    if (!entity.isNull())
    {
        RubroPtr rubro = qSharedPointerDynamicCast<Rubro>(entity);
        material->setRubro(rubro->id());
    }

    material->setName(ui->txtName->text());
    material->setDescription(ui->txtDescription->text());

    close();
}
