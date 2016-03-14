#include "fieldbehaviour.h"

FieldBehaviour::FieldBehaviour(const QString &name,
                               GetterFunctor getter,
                               SetterFunctor setter)
    : QObject(NULL)
{
    _name = name;
    _getter = getter;
    _setter = setter;
}

FieldBehaviour::FieldBehaviour(const QString &name,
                               GetterFunctor getter)
    : QObject(NULL)
{
    _name = name;
    _getter = getter;
    _setter = nullptr;
}

QVariant FieldBehaviour::get(EntityBasePtr entity, int role)
{
    return _getter(entity, role);
}

bool FieldBehaviour::set(EntityBasePtr entity, const QVariant &value, int role)
{
    if (_setter != nullptr)
    {
        return _setter(entity, value, role);
    }
    else
    {
        return true;
    }
}

QString FieldBehaviour::name() const
{
    return _name;
}
