#include "tablewindow.h"
#include "ui_tablewindow.h"

TableWindow::TableWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TableWindow)
{
    ui->setupUi(this);
}

TableWindow::~TableWindow()
{

    delete ui;
}

void TableWindow::setModel(ModelBase* model)
{
    _model = model;
    ui->tableView->setModel(_model);
    ui->tableView->setColumnHidden(0, true);
}

void TableWindow::on_tableView_doubleClicked(const QModelIndex &index)
{
    _model->editEntity(index.row());
}

void TableWindow::on_actionCreate_triggered()
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

void TableWindow::on_actionEdit_triggered()
{

}

void TableWindow::on_actionRemove_triggered()
{

}
