#include "cantidad.h"

Cantidad::Cantidad(double value, UnitPtr unit) : QObject(NULL)
{
    _value = value;
    _unit = unit;
}

Cantidad::Cantidad(double value) : QObject(NULL)
{
    _value = value;
    _unit.clear();
}

QString Cantidad::toString() const
{
    if (_unit.isNull())
    {
        return QString("%1").arg(_value);
    }
    else
    {
        return QString("%1 %2").arg(_value).arg(_unit->name());
    }
}

double Cantidad::value() const
{
    return _value;
}

void Cantidad::setValue(double value)
{
    _value = value;
}
