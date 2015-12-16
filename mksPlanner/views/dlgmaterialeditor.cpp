#include <QDebug>
#include "dlgmaterialeditor.h"
#include "ui_dlgmaterialeditor.h"
#include "globalcontainer.h"
#include "persistance/materialslibrary.h"
#include "views/tablewindow.h"
#include "models/componentesmateriales.h"

dlgMaterialEditor::dlgMaterialEditor(MaterialesBaseModel *model, int row, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgMaterialEditor)
{
    ui->setupUi(this);
    ui->cboUnit->setModel(GlobalContainer::instance().materialLibrary()->model(Tables::Unidades));
    //falta hacer que se vea el nombre de la unidad y que se seleccione el id
    ui->cboUnit->setModelColumn(1);
    _model = model;
    _mapper = new QDataWidgetMapper(this);
    _mapper->setModel(_model);
    _mapper->addMapping(ui->txtName, 1);
    _mapper->addMapping(ui->txtDescription, 2);
    _mapper->addMapping(ui->cboUnit, 3, "currentIndex");
    _mapper->setCurrentIndex(row);
    _mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

    TableWindow *t = new TableWindow("", this);
    //QWidget* w = QWidget::createWindowContainer(t->window(), this);
    EntityBasePtr entity = _model->getItemByRowid(row);
    dynamic_cast<ComponentesMaterialesModel*>(GlobalContainer::instance().materialLibrary()->model(Tables::ComponentesMateriales))->setIdMaterialPadre(entity->id());
    t->setModel(GlobalContainer::instance().materialLibrary()->model(Tables::ComponentesMateriales));

    ui->frame->layout()->addWidget(t->window());
}

dlgMaterialEditor::~dlgMaterialEditor()
{
    delete ui;
}

void dlgMaterialEditor::on_buttonBox_accepted()
{
    qDebug() << ui->cboUnit->currentData();
    qDebug() << ui->cboUnit->currentIndex();
    qDebug() << ui->cboUnit->currentText();
    _mapper->submit();
    close();
}
