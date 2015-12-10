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
