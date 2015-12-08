#include "librarybase.h"

LibraryBase::LibraryBase(QObject *parent) : QObject(parent)
{

}

void LibraryBase::load(const QString &filename)
{
    internalLoadTables();
}

void LibraryBase::save(const QString &filename)
{
    internalSaveTables();
}

void LibraryBase::addModel(const QString &name, ModelBasePtr model)
{
    _models[name] = model;
}

ModelBasePtr LibraryBase::model(const QString &name)
{
    return _models[name];
}
