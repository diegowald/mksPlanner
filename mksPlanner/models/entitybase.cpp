#include "entitybase.h"
#include <QVariant>

EntityBase::EntityBase(QObject *parent) : QObject(parent)
{
    _dirty = false;
    _id = -1;
}

EntityBase::EntityBase(int id, QObject *parent) : QObject(parent)
{
    _dirty = false;
    _id = id;
}

bool EntityBase::setData(const int column, const QVariant &value, int role)
{
    bool res = internalSetData(column, value, role);
    _dirty = true;
    return res;
}

QVariant EntityBase::data(const int column, int role) const
{
    return internalData(column, role);
}

bool EntityBase::isDirty() const
{
    return _dirty;
}

int EntityBase::id() const
{
    return _id;
}
