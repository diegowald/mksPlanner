#include "globalcontainer.h"

GlobalContainer GlobalContainer::_instance;

GlobalContainer::GlobalContainer(QObject *parent) : QObject(parent)
{

}

GlobalContainer &GlobalContainer::instance()
{
    return _instance;
}

void GlobalContainer::setMaterialLibrary(MaterialsLibrary *materialLibrary)
{
    _materialLibrary = materialLibrary;
}

MaterialsLibrary *GlobalContainer::materialLibrary() const
{
    return _materialLibrary;
}

int GlobalContainer::counter(const QString &counterName)
{
    return _counter.contains(counterName) ? _counter[counterName] : -1;
}

void GlobalContainer::setCounter(const QString &counterName, int value)
{
    _counter[counterName] = value;
}
