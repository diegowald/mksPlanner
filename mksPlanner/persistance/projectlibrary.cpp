#include "projectlibrary.h"
#include "models/proyectomodel.h"
#include "models/planningtaskmodel.h"
#include "persistance/projectupdater.h"


ProjectLibrary::ProjectLibrary(const QString &filename, int idProyecto, QObject *parent) : LibraryBase(parent)
{
    _filename = filename;
    _idProyecto = idProyecto;
    updateFromVersion(filename, 0);
    addModel(Tables::Proyectos, new ProyectoModel(_idProyecto, this));
    addModel(Tables::PlanningTasks, new PlanningTaskModel(_idProyecto, this));
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
    ProjectUpdater updater;
    updater.updateFromVersion(filename, versionInfo.toInt());
}
