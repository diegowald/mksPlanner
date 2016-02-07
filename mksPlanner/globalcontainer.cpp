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

int GlobalContainer::createProject(const QString &filename, bool nuevo)
{
    int id = _projectLibraries.count();
    ProjectLibrary *project = new ProjectLibrary(filename, id, nuevo, this);
    _projectLibraries.append(project);
    return id;
}

int GlobalContainer::loadProject(const QString &filename)
{
    int id = createProject(filename, false);
    ProjectLibrary *project = projectLibrary(id);
    project->setFileName(filename);
    project->load();
    return id;
}

bool GlobalContainer::unsavedProjects() const
{
    foreach (ProjectLibrary *p, _projectLibraries)
    {
        if (p->isDirty())
            return true;
    }
    return false;
}

void GlobalContainer::saveAllProjects()
{
    foreach (ProjectLibrary *p, _projectLibraries)
    {
        if (p->isDirty())
            p->save();
    }
}
