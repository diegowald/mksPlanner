#include "unitsmodel.h"

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
        return _value;
    }
    return QVariant();
}

QVariant UnitsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        return QString("Header");
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
    return Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}
