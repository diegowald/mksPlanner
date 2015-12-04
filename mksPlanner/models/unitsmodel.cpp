#include "unitsmodel.h"
#include <QDebug>


UnitsModel::UnitsModel(QObject *parent) : QAbstractTableModel(parent)
{
    _value = "Hola";
}

int UnitsModel::rowCount(const QModelIndex &/*parent*/) const
{
    return 2;
}

int UnitsModel::columnCount(const QModelIndex &/*parent*/) const
{
    return 2;
}

QVariant UnitsModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        qDebug() << index.row() << ", " << index.column();
        return _value;
    }
    else if (role == Qt::EditRole)
    {
        return _value;
    }
    else
    {
        return QVariant();
    }
}

QVariant UnitsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        return section;
    }
    return QAbstractItemModel::headerData(section, orientation, role);
}

bool UnitsModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role == Qt::EditRole)
    {
        _value = value.toString();
        // Data edited
    }
    return true;
}

Qt::ItemFlags UnitsModel::flags(const QModelIndex &index) const
{
    return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
//    return Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}
