#include "projectlibrary.h"
#include "models/proyectomodel.h"
#include "persistance/materialesupdater.h"

ProjectLibrary::ProjectLibrary(QObject *parent) : LibraryBase(parent)
{
    addModel(Tables::Proyectos, new ProyectoModel(this));
}

void ProjectLibrary::internalSaveTables(const QString &filename)
{
    model(Tables::Proyectos)->save(filename);
}

void ProjectLibrary::internalLoadTables(const QString &filename)
{
    model(Tables::Proyectos)->load(filename);
}

void ProjectLibrary::updateFromVersion(const QString &filename, const QString &versionInfo)
{
    MaterialesUpdater updater;
    updater.updateFromVersion(filename, versionInfo.toInt());
}
