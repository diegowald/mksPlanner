#include "dlgeditproject.h"
#include "ui_dlgeditproject.h"

dlgEditProject::dlgEditProject(ProyectoModel *model, int row, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgEditProject)
{
    ui->setupUi(this);
}

dlgEditProject::~dlgEditProject()
{
    delete ui;
}
