#include "unitswindow.h"
#include "ui_unitswindow.h"
#include "views/dlguniteditor.h"

UnitsWindow::UnitsWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UnitsWindow)
{
    ui->setupUi(this);
    _model = new UnitsModel(this);
    ui->tableView->setModel(_model);
}

UnitsWindow::~UnitsWindow()
{
    delete ui;
}

void UnitsWindow::on_tableView_doubleClicked(const QModelIndex &index)
{
    dlgUnitEditor dlg(_model, index.row(), this);
    dlg.exec();
}
