#include "globalcontainer.h"

GlobalContainer *GlobalContainer::_instance;

GlobalContainer::GlobalContainer(QObject *parent) : QObject(parent)
{
    _library = NULL;
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

void GlobalContainer::setLibrary(MaterialsLibrary *library)
{
    if (_library != NULL)
    {
        _library->deleteLater();
    }
    _library = library;
}

MaterialsLibrary *GlobalContainer::library() const
{
    return _library;
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

int GlobalContainer::createProject(const QString &filename)
{
    int id = _projectLibraries.count();
    ProjectLibrary *project = new ProjectLibrary(filename, id, this);
    _projectLibraries.append(project);
    return id;
}

int GlobalContainer::loadProject(const QString &filename)
{
    int id = createProject(filename);
    ProjectLibrary *project = projectLibrary(id);
    project->load(filename);
    return id;
}
