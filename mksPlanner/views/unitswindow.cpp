#include "unitswindow.h"
#include "ui_unitswindow.h"
#include "views/dlguniteditor.h"

UnitsWindow::UnitsWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UnitsWindow)
{
    ui->setupUi(this);
    _model = new UnitsModel(/*"./materiales.db",*/ this);
    _model->load();
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

void UnitsWindow::on_actionCreate_triggered()
{
    QModelIndex index = ui->tableView->selectionModel()->currentIndex();


    if (!_model->insertRow(index.row() + 1, index.parent()))
        return;

/*    updateActions();

    for (int column = 0; column < model->columnCount(index.parent()); ++column) {
        QModelIndex child = model->index(index.row()+1, column, index.parent());
        model->setData(child, QVariant("[No data]"), Qt::EditRole);
    }

    QModelIndex index;
    _model->insertRow(0, index);*/
}

void UnitsWindow::on_actionEdit_triggered()
{

}

void UnitsWindow::on_actionRemove_triggered()
{

}

void UnitsWindow::save()
{
    _model->save();
}
