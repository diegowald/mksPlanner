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
    UnitsWindow *frm = new UnitsWindow();
    QMdiSubWindow *subWnd = ui->mdiArea->addSubWindow(frm);
    frm->setAttribute(Qt::WA_DeleteOnClose);
    subWnd->show();
}

void MainWindow::loadMaterialLibrary()
{
}

void MainWindow::loadProject(const QString &fileName)
{
}
