#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "views/tablewindow.h"
#include <qmdisubwindow.h>
#include "persistance/materialslibrary.h"
#include "globalcontainer.h"
#include "persistance/projectlibrary.h"
#include "views/projectwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    GlobalContainer::initialize();
    loadMaterialLibrary();
}

MainWindow::~MainWindow()
{
    GlobalContainer::finalize();
    delete ui;
}

void MainWindow::on_actionSalir_triggered()
{
    //QApplication::exit(0);
    close();
}

bool MainWindow::showSubWindow(const QString &windowName)
{
    QMdiSubWindow *subWindow = ui->mdiArea->findChild<QMdiSubWindow*>(windowName);
    if (subWindow == NULL)
    {
        return false;
    }
    else
    {
        subWindow->activateWindow();
        subWindow->show();
        subWindow->setFocus();
        return true;
    }
}

void MainWindow::createSubWindow(const QString &windowName, QWidget *widget)
{
    QMdiSubWindow *subWindow = ui->mdiArea->addSubWindow(widget);
    subWindow->setObjectName(windowName);
    widget->setAttribute(Qt::WA_DeleteOnClose);
    subWindow->show();
}

void MainWindow::on_actionUnidades_triggered()
{
    if (!showSubWindow("Unidades de medida"))
    {
        TableWindow *frm = new TableWindow("Unidades de medida");
        frm->setModel(GlobalContainer::instance().materialLibrary()->model(Tables::Unidades));
        createSubWindow("Unidades de medida", frm);
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
    if (!showSubWindow("Proyecto"))
    {
        int id = GlobalContainer::instance().loadProject(fileName);
        ProjectWindow *frm = new ProjectWindow("Proyecto");
        frm->setModel(GlobalContainer::instance().projectLibrary(id)->model(Tables::Proyectos));
        createSubWindow("Proyecto", frm);
    }
}

void MainWindow::on_actionSave_Material_Library_triggered()
{
    GlobalContainer::instance().materialLibrary()->save("./materiales.db");
}

void MainWindow::on_actionVer_Biblioteca_triggered()
{
    if (!showSubWindow("Biblioteca de Materiales"))
    {
        TableWindow* frm = new TableWindow("Biblioteca de materiales");
        frm->setModel(GlobalContainer::instance().materialLibrary()->model(Tables::Materiales));
        createSubWindow("Biblioteca de Materiales", frm);
    }
}
void MainWindow::on_actionTareas_triggered()
{
    if (!showSubWindow("Tareas"))
    {
        TableWindow *frm = new TableWindow("Tareas");
        frm->setModel(GlobalContainer::instance().materialLibrary()->model(Tables::Tareas));
        createSubWindow("Tareas", frm);
    }
}

void MainWindow::on_actionListado_triggered()
{
    if (!showSubWindow("Proveedores"))
    {
        TableWindow *frm = new TableWindow("Proveedores");
        frm->setModel(GlobalContainer::instance().materialLibrary()->model(Tables::Proveedores));
        createSubWindow("Proveedores", frm);
    }
}

void MainWindow::on_actionCalculadora_de_materiales_triggered()
{

}

void MainWindow::on_actionNuevo_triggered()
{
    if (!showSubWindow("Proyecto"))
    {
        int tmpId = GlobalContainer::instance().createProject();
        ProjectWindow *frm = new ProjectWindow("Proyecto");
        frm->setModel(GlobalContainer::instance().projectLibrary(tmpId)->model(Tables::Proyectos));
        createSubWindow("Proyecto", frm);
    }
}
