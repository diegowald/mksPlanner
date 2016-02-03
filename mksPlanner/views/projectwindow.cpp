#include "projectwindow.h"
#include "ui_projectwindow.h"

ProjectWindow::ProjectWindow(const QString &windowTitle, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ProjectWindow)
{
    ui->setupUi(this);
    setWindowTitle(windowTitle);
    _mapper = NULL;
}

ProjectWindow::~ProjectWindow()
{
    delete ui;
}


void ProjectWindow::setModel(ModelBase* model)
{
    _model = model;
    if (_mapper != NULL)
    {
        _mapper->deleteLater();
    }
    _mapper = new QDataWidgetMapper(this);
    _mapper->setModel(model);

    _mapper->addMapping(ui->txtPropietario, model->columnIndex("Propietario"));
    _mapper->addMapping(ui->txtDireccion, model->columnIndex("Direccion"));
    _mapper->addMapping(ui->txtEmail, model->columnIndex("Email"));
    _mapper->addMapping(ui->txtTelefono, model->columnIndex("Telefono"));
    _mapper->addMapping(ui->dateEstimacionInicio, model->columnIndex("Fecha estimada de Inicio"));
    _mapper->addMapping(ui->dateEstimacionFinalizacion, model->columnIndex("Fecha estimada de finalización"));

    _mapper->setCurrentIndex(0);
    _mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
}

void ProjectWindow::setPlanningModel(ModelBase *model)
{
    _planningModel = model;
    ui->planningView->setModel(_planningModel);
}

void ProjectWindow::on_tabWidget_currentChanged(int index)
{
    switch (index)
    {
    case 0:
        break;
    default:
        break;
    }
}
