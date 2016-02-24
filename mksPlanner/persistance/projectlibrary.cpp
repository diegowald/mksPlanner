#include "projectlibrary.h"
#include "models/proyectomodel.h"
#include "models/planningtaskmodel.h"
#include "persistance/projectupdater.h"
#include "models/planningtaskmodelconstraint.h"

ProjectLibrary::ProjectLibrary(const QString &filename, int idProyecto, bool nuevo,  QObject *parent) : LibraryBase(parent)
{
    setFileName(filename);
    _idProyecto = idProyecto;
    updateFromVersion(filename, 0);
    addModel(Tables::Proyectos, new ProyectoModel(_idProyecto, this));
    addModel(Tables::PlanningTasks, new PlanningTaskModel(_idProyecto, this));
    addModel(Tables::PlanningTasksConstraints, new PlanningTaskModelConstraint(_idProyecto, this));

    if (nuevo)
    {
        model(Tables::Proyectos)->createEntity();
    }
}

void ProjectLibrary::internalSaveTables(const QString &filename)
{
    model(Tables::Proyectos)->save(filename);
    model(Tables::PlanningTasks)->save(filename);
    model(Tables::PlanningTasksConstraints)->save(filename);
}

void ProjectLibrary::internalLoadTables(const QString &filename)
{
    model(Tables::Proyectos)->load(filename);
    model(Tables::PlanningTasks)->load(filename);
    model(Tables::PlanningTasksConstraints)->load(filename);
}

void ProjectLibrary::updateFromVersion(const QString &filename, const QString &versionInfo)
{
    ProjectUpdater updater;
    updater.updateFromVersion(filename, versionInfo.toInt());
}
