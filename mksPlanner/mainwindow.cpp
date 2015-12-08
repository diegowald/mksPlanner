#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "views/unitswindow.h"
#include <qmdisubwindow.h>

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
        UnitsWindow *frm = new UnitsWindow();
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
}

void MainWindow::loadProject(const QString &fileName)
{
}

void MainWindow::on_actionSave_Material_Library_triggered()
{
    if (unitsSubWindow != NULL)
    {
        UnitsWindow *frm = (UnitsWindow*) unitsSubWindow->widget();
        frm->save();
    }
}
