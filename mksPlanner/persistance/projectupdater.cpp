#include "projectupdater.h"


ProjectUpdater::ProjectUpdater(QObject *parent) : Updater(parent)
{
    scriptsVersion1();
}

void ProjectUpdater::scriptsVersion1()
{
    addCommand(1, "CREATE TABLE `version` (`versionInfo` INTEGER);");

    addCommand(1,
               "CREATE TABLE `proyectos` ( "
               "    `id`	INTEGER NOT NULL UNIQUE, "
               "    `propietario`	TEXT NOT NULL, "
               "    `direccion`	TEXT, "
               "    `email`	TEXT, "
               "    `telefono`	TEXT, "
               "    `fechaEstimadaInicio`	TEXT, "
               "    `fechaEstimadaFinalizacion`	TEXT, "
               "    PRIMARY KEY(id) "
               " ); ");

    addCommand(1,
               "CREATE TABLE `tareasPlanificadas` ( "
               "    `id`	INTEGER NOT NULL UNIQUE, "
               "    `idTareaPadre`	INTEGER, "
               "    `name`	INTEGER, "
               "    `idMaterialTask`	INTEGER, "
               "    `idProveedor`	INTEGER, "
               "    `cantidad`	REAL, "
               "    `fechaEstimadaInicio`	TEXT, "
               "    `fechaEstimadaFin`	TEXT, "
               "    `taskType`	INTEGER, "
               "    PRIMARY KEY(id) "
               "); ");

    addCommand(1,
               "CREATE TABLE `tareasPlanificadasConstraints` ("
               "    `id`	INTEGER NOT NULL UNIQUE,"
               "    `idTask1`	INTEGER,"
               "    `idTask2`	INTEGER,"
               "    `type`	INTEGER,"
               "    `relationType`	INTEGER,"
               "    PRIMARY KEY(id)"
               ");");

    addCommand(1, "INSERT into version (versionInfo) VALUES (1)");
}
