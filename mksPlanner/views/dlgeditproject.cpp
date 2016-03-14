#include "dlgeditproject.h"
#include "ui_dlgeditproject.h"

dlgEditProject::dlgEditProject(ProyectoModel *, int, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgEditProject)
{
    ui->setupUi(this);
}

dlgEditProject::~dlgEditProject()
{
    delete ui;
}
