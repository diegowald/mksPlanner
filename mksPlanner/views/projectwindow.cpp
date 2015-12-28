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

    _mapper->addMapping(ui->txtPropietario, 1);
    _mapper->addMapping(ui->txtDireccion, 2);
    _mapper->addMapping(ui->txtEmail, 3);
    _mapper->addMapping(ui->txtTelefono, 4);

    _mapper->setCurrentIndex(0);
    _mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

}
