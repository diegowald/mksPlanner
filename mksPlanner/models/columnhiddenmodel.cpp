#include "columnhiddenmodel.h"
#include <QModelIndex>
#include <QSet>

ColumnHiddenModel::ColumnHiddenModel(IModel* model, QObject *parent) : QAbstractTableModel(parent)
{
    _model = model;
}

ColumnHiddenModel::~ColumnHiddenModel()
{
}

int ColumnHiddenModel::rowCount(const QModelIndex &parent) const
{
    return _model->rowCount(parent);
}


int ColumnHiddenModel::columnCount(const QModelIndex &parent) const
{
    return _model->columnCount(parent) - _columnsHidden.count();
}

int ColumnHiddenModel::calculateColumn(int column) const
{
    int columnaRecalculada = column;
    foreach(int ch, _columnsHidden.values())
    {
        if (ch < column)
            columnaRecalculada++;
    }
    return columnaRecalculada;
}


QVariant ColumnHiddenModel::data(const QModelIndex &index, int role) const
{
    int columnaRecalculada = calculateColumn(index.column());

    EntityBasePtr e = _model->getItemByRowid(index.row());
    return _model->data(e->id(), columnaRecalculada, role);
}

QVariant ColumnHiddenModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    int columnaRecalculada = calculateColumn(section);
    return _model->headerData(columnaRecalculada, orientation, role);
}

void ColumnHiddenModel::addColumnToHide(int column)
{
    _columnsHidden.insert(column);
}
