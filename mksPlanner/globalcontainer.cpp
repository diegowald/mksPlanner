#include "globalcontainer.h"

GlobalContainer GlobalContainer::_instance;

GlobalContainer::GlobalContainer(QObject *parent) : QObject(parent)
{
    _projectLibrary = NULL;
    _materialLibrary = NULL;
}

GlobalContainer &GlobalContainer::instance()
{
    return _instance;
}

void GlobalContainer::setMaterialLibrary(MaterialsLibrary *materialLibrary)
{
    if (_materialLibrary != NULL)
    {
        _materialLibrary->deleteLater();
    }
    _materialLibrary = materialLibrary;
}

MaterialsLibrary *GlobalContainer::materialLibrary() const
{
    return _materialLibrary;
}

void GlobalContainer::setProjectLibrary(ProjectLibrary *projectLibrary)
{
    if (_projectLibrary != NULL)
    {
        _projectLibrary->deleteLater();
    }
    _projectLibrary = projectLibrary;
}

ProjectLibrary *GlobalContainer::projectLibrary() const
{
    return _projectLibrary;
}


int GlobalContainer::counter(const QString &counterName)
{
    return _counter.contains(counterName) ? _counter[counterName] : -1;
}

void GlobalContainer::setCounter(const QString &counterName, int value)
{
    _counter[counterName] = value;
}
