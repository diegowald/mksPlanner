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

void LibraryBase::addModel(Tables name, ModelBase* model)
{
    _models[name] = model;
}

ModelBase *LibraryBase::model(Tables name)
{
    return _models[name];
}
