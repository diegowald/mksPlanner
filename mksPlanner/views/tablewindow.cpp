#include "tablewindow.h"
#include "ui_tablewindow.h"
#include <QModelIndex>

TableWindow::TableWindow(const QString &windowTitle, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TableWindow)
{
    ui->setupUi(this);
    setWindowTitle(windowTitle);
    _inPlaceEdit = false;
}

TableWindow::~TableWindow()
{
    delete ui;
}

void TableWindow::setModel(ModelBase* model)
{
    _model = model;
    if (_model->implementsDelegate())
    {
        ui->tableView->setItemDelegate(_model->delegate());
    }
    ui->tableView->setModel(_model);
    ui->tableView->setColumnHidden(0, true);
}

void TableWindow::on_tableView_doubleClicked(const QModelIndex &index)
{
    if (!_inPlaceEdit)
        _model->editEntity(index.row());
    else
    {
        ui->tableView->edit(index);
    }
}

void TableWindow::on_actionCreate_triggered()
{
    int rowCount = ui->tableView->model()->rowCount();
    QModelIndex index = ui->tableView->selectionModel()->currentIndex();


    if (!_model->insertRow(rowCount /*index.row() + 1*/, index.parent()))
        return;

    _model->editEntity(rowCount/*index.row() + 1*/);
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
    QModelIndex index = ui->tableView->selectionModel()->currentIndex();
    _model->editEntity(index.row());
}

void TableWindow::on_actionRemove_triggered()
{
    QModelIndex index = ui->tableView->selectionModel()->currentIndex();
    _model->removeEntity(this->window(), index.row());
}

void TableWindow::hideColumn(int idColumn)
{
    ui->tableView->setColumnHidden(idColumn, true);
}

void TableWindow::setInPlaceEditable(bool value)
{
    _inPlaceEdit = value;
}
