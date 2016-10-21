#include "columnhiddenmodel.h"
#include <QModelIndex>
#include <QSet>
#include <QDebug>
#include <QList>


ColumnHiddenModel::ColumnHiddenModel(IModel* model, QObject *parent) : QAbstractTableModel(parent)
{
    _model = model;
    _columnsVisible.clear();
    setupVisibleColumns();
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
    //return _model->columnCount(parent) - _columnsHidden.count();
    return _columnsVisible.count();
}

/*
int ColumnHiddenModel::calculateColumn(int column) const
{
    int columnaRecalculada = column;
    foreach(int ch, _columnsHidden.values())
    {
        if (ch < columnaRecalculada)
            columnaRecalculada++;
    }
    return columnaRecalculada;
}
*/

QVariant ColumnHiddenModel::data(const QModelIndex &index, int role) const
{
    //int columnaRecalculada = calculateColumn(index.column());
    int columnaRecalculada = _columnsVisible.at(index.column());

    EntityBasePtr e = _model->getItemByRowid(index.row());
    return _model->data(e->id(), columnaRecalculada, role);
}

QVariant ColumnHiddenModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    qDebug() << "antes de calcular la columna " << section;
    //int columnaRecalculada = calculateColumn(section);
    int columnaRecalculada = _columnsVisible.at(section);
    qDebug() << "despies de calcular la columna " << columnaRecalculada;
    return _model->headerData(columnaRecalculada, orientation, role);
}

void ColumnHiddenModel::addColumnToHide(int column)
{
    _columnsHidden.insert(column);
    setupVisibleColumns();
}

void ColumnHiddenModel::setupVisibleColumns()
{
    _columnsVisible.clear();
    for (int i = 0; i < _model->columnCount(); ++i)
    {
        if (!_columnsHidden.contains(i))
        {
            _columnsVisible.append(i);
        }
    }
}
