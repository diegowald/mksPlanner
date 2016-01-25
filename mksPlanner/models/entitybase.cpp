#include "entitybase.h"
#include <QVariant>

EntityBase::EntityBase() : QObject(0)
{
    _id = -1;
    _status = EntityStatus::added;
}

EntityBase::EntityBase(int id, bool isNew) : QObject(0)
{
    _id = id;
    _status = isNew ? EntityStatus::added : EntityStatus::unchanged;
}

/*bool EntityBase::setData(const int column, const QVariant &value, int role)
{
    bool res = internalSetData(column, value, role);
    updateStatus(EntityStatus::modified);
    return res;
}*/

int EntityBase::id() const
{
    return _id;
}

void EntityBase::deleteEntity()
{
    updateStatus(EntityStatus::deleted);
}

EntityStatus EntityBase::status()
{
    return _status;
}

void EntityBase::updateStatus(EntityStatus newStatus)
{
    switch (newStatus) {
    case EntityStatus::unchanged:
        _status = newStatus;
        break;
    case EntityStatus::added:
        _status = newStatus;
        break;
    case EntityStatus::modified:
        _status = _status != EntityStatus::added ? newStatus : _status;
        break;
    case EntityStatus::deleted:
        _status = _status == EntityStatus::added ? EntityStatus::unchanged : newStatus;
        break;
    }
}
