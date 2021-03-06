#include "tablewindow.h"
#include "ui_tablewindow.h"
#include <QModelIndex>
#include "globalcontainer.h"

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

void TableWindow::setModel(IModel *model)
{
    _model = model;
    if (_model->implementsDelegate())
    {
        ui->tableView->setItemDelegate(_model->delegate());
    }
    ui->tableView->setModel(_model);
    ui->tableView->setColumnHidden(0, true);
    ui->actionCreate->setEnabled(model->canCreateEntity());
    connect(static_cast<ModelBase*>(model), &ModelBase::changed, this, &TableWindow::on_modelChanged);
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


    if (!_model->insertRow(rowCount, index.parent()))
        return;

    _model->editEntity(rowCount);
}

void TableWindow::on_actionEdit_triggered()
{
    QModelIndex index = ui->tableView->selectionModel()->currentIndex();
    _model->editEntity(index.row());
}

void TableWindow::on_actionRemove_triggered()
{
    QModelIndex index = ui->tableView->selectionModel()->currentIndex();
    _model->removeEntity(window(), index);
}

void TableWindow::hideColumn(int idColumn)
{
    ui->tableView->setColumnHidden(idColumn, true);
}

void TableWindow::setInPlaceEditable(bool value)
{
    _inPlaceEdit = value;
}

void TableWindow::on_modelChanged(Tables /*table*/)
{
    ui->actionCreate->setEnabled(_model->canCreateEntity());
}
