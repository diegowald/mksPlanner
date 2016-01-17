#include "globalcontainer.h"

GlobalContainer *GlobalContainer::_instance;

GlobalContainer::GlobalContainer(QObject *parent) : QObject(parent)
{
    _materialLibrary = NULL;
}

void GlobalContainer::initialize()
{
    _instance = new GlobalContainer();
}

void GlobalContainer::finalize()
{
    _instance->deleteLater();
}

GlobalContainer &GlobalContainer::instance()
{
    return *_instance;
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

ProjectLibrary *GlobalContainer::projectLibrary(int id) const
{
    return _projectLibraries.at(id);
}


int GlobalContainer::counter(const QString &counterName)
{
    return _counter.contains(counterName) ? _counter[counterName] : -1;
}

void GlobalContainer::setCounter(const QString &counterName, int value)
{
    _counter[counterName] = value;
}

int GlobalContainer::createProject()
{
    int id = _projectLibraries.count();
    ProjectLibrary *project = new ProjectLibrary(this);
    _projectLibraries.append(project);
    return id;
}

int GlobalContainer::loadProject(const QString &filename)
{
    int id = createProject();
    ProjectLibrary *project = projectLibrary(id);
    project->load(filename);
    return id;
}
