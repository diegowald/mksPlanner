#include "modelfromtablewidget.h"
#include <QVariant>
#include <QTableWidgetItem>
#include <QDebug>

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
    qDebug() << index.row() << ", " << index.column() << " (" << role << "): " << _widget->item(index.row(), index.column())->data(role);
    return _widget->item(index.row(), index.column())->data(role);
}

QVariant ModelFromTableWidget::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal)
    {
        return _widget->horizontalHeaderItem(section)->text();
    }
    else
    {
        return QAbstractTableModel::headerData(section, orientation, role);
    }
}
