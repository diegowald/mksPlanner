#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "views/tablewindow.h"
#include <qmdisubwindow.h>
#include "persistance/materialslibrary.h"
#include "globalcontainer.h"
#include "persistance/projectlibrary.h"
#include "views/projectwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QCloseEvent>

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
    subWindow->setWindowIcon(widget->windowIcon());
    subWindow->show();
}

void MainWindow::on_actionUnidades_triggered()
{
    if (!showSubWindow("Unidades de medida"))
    {
        TableWindow *frm = new TableWindow("Unidades de medida");
        frm->setModel(GlobalContainer::instance().library()->model(Tables::Unidades));
        createSubWindow("Unidades de medida", frm);
    }
}

void MainWindow::loadMaterialLibrary()
{
    MaterialsLibrary* materialsLibrary = new MaterialsLibrary();
    GlobalContainer::instance().setLibrary(materialsLibrary);
    materialsLibrary->setFileName("./materiales.db");
    materialsLibrary->load();
}

void MainWindow::loadProject(const QString &fileName)
{
    if (!showSubWindow("Proyecto"))
    {
        int id = GlobalContainer::instance().loadProject(fileName);
        ProjectWindow *frm = new ProjectWindow("Proyecto", id);
        frm->setModel(GlobalContainer::instance().projectLibrary(id)->model(Tables::Proyectos));
        createSubWindow("Proyecto", frm);
    }
}

void MainWindow::on_actionSave_Material_Library_triggered()
{
    GlobalContainer::instance().library()->save();
}

void MainWindow::on_actionVer_Biblioteca_triggered()
{
    if (!showSubWindow("Biblioteca de Materiales"))
    {
        TableWindow* frm = new TableWindow("Biblioteca de materiales");
        frm->setModel(GlobalContainer::instance().library()->model(Tables::Materiales));
        createSubWindow("Biblioteca de Materiales", frm);
    }
}

void MainWindow::on_actionListado_triggered()
{
    if (!showSubWindow("Proveedores"))
    {
        TableWindow *frm = new TableWindow("Proveedores");
        frm->setModel(GlobalContainer::instance().library()->model(Tables::Proveedores));
        createSubWindow("Proveedores", frm);
    }
}

void MainWindow::on_actionNuevo_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this, "Crear proyecto", "./", "*.mksPlanner");
    if (filename.length() != 0)
    {
        if (!filename.endsWith(".mksPlanner"))
        {
            filename += ".mksPlanner";
        }
        QFile file(filename);
        if (file.exists())
            file.remove();
        if (!showSubWindow("Proyecto"))
        {
            int tmpId = GlobalContainer::instance().createProject(filename);
            ProjectWindow *frm = new ProjectWindow("Proyecto", tmpId);
            frm->setModel(GlobalContainer::instance().projectLibrary(tmpId)->model(Tables::Proyectos));
            frm->setPlanningModel(GlobalContainer::instance().projectLibrary(tmpId)->model(Tables::PlanningTasks));
            frm->setConstraintModel(GlobalContainer::instance().projectLibrary(tmpId)->model(Tables::PlanningTasksConstraints));
            frm->setExecutionModel(GlobalContainer::instance().projectLibrary(tmpId)->model(Tables::ExecutionTasks));
            frm->setExecutionConstraintModel(GlobalContainer::instance().projectLibrary(tmpId)->model(Tables::ExecutionTasksConstraints));
            createSubWindow("Proyecto", frm);
            frm->setIconResource(":/tableWindow/tools/planning");
        }
    }
}

void MainWindow::on_actionAbrir_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, "Crear proyecto", "./", "*.mksPlanner");
    if (!showSubWindow("Proyecto"))
    {
        int tmpId = GlobalContainer::instance().loadProject(filename);
        ProjectWindow *frm = new ProjectWindow("Proyecto", tmpId);
        frm->setModel(GlobalContainer::instance().projectLibrary(tmpId)->model(Tables::Proyectos));
        frm->setPlanningModel(GlobalContainer::instance().projectLibrary(tmpId)->model(Tables::PlanningTasks));
        frm->setConstraintModel(GlobalContainer::instance().projectLibrary(tmpId)->model(Tables::PlanningTasksConstraints));
        frm->setExecutionModel(GlobalContainer::instance().projectLibrary(tmpId)->model(Tables::ExecutionTasks));
        frm->setExecutionConstraintModel(GlobalContainer::instance().projectLibrary(tmpId)->model(Tables::ExecutionTasksConstraints));
        createSubWindow("Proyecto", frm);
        frm->setIconResource(":/tableWindow/tools/planning");
    }
}

void MainWindow::on_actionRubros_triggered()
{
    if (!showSubWindow("Rubros"))
    {
        TableWindow *frm = new TableWindow("Rubros");
        frm->setModel(GlobalContainer::instance().library()->model(Tables::Rubros));
        createSubWindow("Rubros", frm);
    }
}

void MainWindow::on_actionCostos_triggered()
{
    if (!showSubWindow("Costos"))
    {
        TableWindow *frm = new TableWindow("Costos");
        frm->setModel(GlobalContainer::instance().library()->model(Tables::CostosUnitarios));
        createSubWindow("Costos", frm);
    }
}

void MainWindow::closeEvent(QCloseEvent *evt)
{
    if (GlobalContainer::instance().library()->isDirty())
    {
        QMessageBox::StandardButton resBtn = QMessageBox::question( this, "mksPlanner",
                                                                    "Guarda biblioteca?",
                                                                    QMessageBox::Cancel /*| QMessageBox::No */| QMessageBox::Yes,
                                                                    QMessageBox::Yes);
        if (resBtn != QMessageBox::Yes)
        {
            evt->ignore();
        }
        else
        {
            on_actionSave_Material_Library_triggered();
            evt->accept();
        }
    }

    if (GlobalContainer::instance().unsavedProjects())
    {
        QMessageBox::StandardButton resBtn = QMessageBox::question( this, "mksPlanner",
                                                                    "Guarda proyectos?",
                                                                    QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
                                                                    QMessageBox::Yes);
        switch (resBtn)
        {
        case QMessageBox::Yes:
            GlobalContainer::instance().saveAllProjects();
        case QMessageBox::No:
            evt->accept();
            break;
        default:
            evt->ignore();
        }
    }
}
