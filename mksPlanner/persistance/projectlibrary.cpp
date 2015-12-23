#include "projectlibrary.h"
#include "models/proyectomodel.h"

ProjectLibrary::ProjectLibrary(QObject *parent) : LibraryBase(parent)
{
    addModel(Tables::Projectos, new ProyectoModel(this));
}

void ProjectLibrary::internalSaveTables(const QString &filename)
{
    model(Tables::Projectos)->save(filename);
}

void ProjectLibrary::internalLoadTables(const QString &filename)
{
    model(Tables::Projectos)->load(filename);
}
