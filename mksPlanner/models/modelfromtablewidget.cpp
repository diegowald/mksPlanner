#include "modelfromtablewidget.h"
#include <QVariant>
#include <QTableWidgetItem>

ModelFromTableWidget::ModelFromTableWidget(QTableWidget *widget, QObject *parent) :
    QAbstractTableModel(parent)
{
    _widget = widget;
}

ModelFromTableWidget::~ModelFromTableWidget()
{
}

int ModelFromTableWidget::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return _widget->rowCount();
}

int ModelFromTableWidget::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return _widget->columnCount();
}

QVariant ModelFromTableWidget::data(const QModelIndex &index, int role) const
{
    return _widget->item(index.row(), index.column())->data(role);
}
