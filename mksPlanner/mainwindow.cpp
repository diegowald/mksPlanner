#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "views/tablewindow.h"
#include <qmdisubwindow.h>
#include "persistance/materialslibrary.h"
#include "globalcontainer.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loadMaterialLibrary();
    unitsSubWindow = NULL;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionSalir_triggered()
{
    //QApplication::exit(0);
    close();
}

void MainWindow::on_actionUnidades_triggered()
{
    if (unitsSubWindow == NULL)
    {
        TableWindow *frm = new TableWindow();
        frm->setModel(GlobalContainer::instance().materialLibrary()->model(Tables::Unidades));
        unitsSubWindow = ui->mdiArea->addSubWindow(frm);
        frm->setAttribute(Qt::WA_DeleteOnClose);
        unitsSubWindow->show();
    }
    else
    {
        unitsSubWindow->activateWindow();
    }
}

void MainWindow::loadMaterialLibrary()
{
    MaterialsLibrary* materialsLibrary = new MaterialsLibrary();
    materialsLibrary->load("./materiales.db");
    GlobalContainer::instance().setMaterialLibrary(materialsLibrary);
}

void MainWindow::loadProject(const QString &fileName)
{
}

void MainWindow::on_actionSave_Material_Library_triggered()
{
    GlobalContainer::instance().materialLibrary()->save("./materiales.db");
}

void MainWindow::on_actionVer_Biblioteca_triggered()
{
    TableWindow* frm = new TableWindow();
    frm->setModel(GlobalContainer::instance().materialLibrary()->model(Tables::Materiales));
    QMdiSubWindow* subWindow = ui->mdiArea->addSubWindow(frm);
    frm->setAttribute(Qt::WA_DeleteOnClose);
    subWindow->show();
}

void MainWindow::on_actionTareas_triggered()
{
    TableWindow *frm = new TableWindow();
    frm->setModel(GlobalContainer::instance().materialLibrary()->model(Tables::Tareas));
    QMdiSubWindow* subWindow = ui->mdiArea->addSubWindow(frm);
    frm->setAttribute(Qt::WA_DeleteOnClose);
    subWindow->show();
}

void MainWindow::on_actionListado_triggered()
{
    TableWindow *frm = new TableWindow();
    frm->setModel(GlobalContainer::instance().materialLibrary()->model(Tables::Proveedores));
    QMdiSubWindow* subWindow = ui->mdiArea->addSubWindow(frm);
    frm->setAttribute(Qt::WA_DeleteOnClose);
    subWindow->show();
}
