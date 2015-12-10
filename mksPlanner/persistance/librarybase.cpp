#include "librarybase.h"

LibraryBase::LibraryBase(QObject *parent) : QObject(parent)
{

}

void LibraryBase::load(const QString &filename)
{
    internalLoadTables(filename);
}

void LibraryBase::save(const QString &filename)
{
    internalSaveTables(filename);
}

void LibraryBase::addModel(const QString &name, ModelBase* model)
{
    _models[name] = model;
}

ModelBase *LibraryBase::model(const QString &name)
{
    return _models[name];
}
