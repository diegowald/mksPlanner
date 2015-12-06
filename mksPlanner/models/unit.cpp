#include "unit.h"
#include <QVariant>


Unit::Unit(int id, QString &name, QString &description, QObject *parent) : EntityBase(id, parent)
{
    _name = name;
    _description = description;
}

bool Unit::internalSetData(const int column, const QVariant &value, int role)
{
    switch (column)
    {
    case 0:
        _name = value.toString();
        return true;
        break;
    case 1:
        _description = value.toString();
        return true;
        break;
    default:
        break;
    }
    return false;
}

QVariant Unit::internalData(const int column, int role) const
{
    switch (column)
    {
    case 0:
        return _name;
        break;
    case 1:
        return _description;
        break;
    default:
        return QVariant();
        break;
    }
}
