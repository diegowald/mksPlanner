#include "projectupdater.h"


ProjectUpdater::ProjectUpdater(QObject *parent) : Updater(parent)
{
    scriptsVersion1();
    scriptsVersion2();
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


void ProjectUpdater::scriptsVersion2()
{
    addCommand(2, "ALTER TABLE proyectos ADD COLUMN `status` INTEGER;");

    addCommand(2, "UPDATE proyectos set status = 0;");

    addCommand(2, "CREATE TABLE `tareasEjecucion` ("
                  "    `id`	INTEGER NOT NULL UNIQUE,"
                  "    `idTareaPadre`	INTEGER,"
                  "    `name`	TEXT,"
                  "    `idMaterialTask`	INTEGER,"
                  "    `idProveedor`	INTEGER,"
                  "    `cantidad`	REAL,"
                  "    `fechaEstimadaInicio`	TEXT,"
                  "    `fechaEstimadaFin`	TEXT,"
                  "    `taskType`	INTEGER,"
                  "    `pctAvance`	REAL,"
                  "    `fechaRealInicio`	TEXT,"
                  "    `fechaRealFin`	TEXT,"
                  "    `isSplittedPart` INTEGER, "
                  "    PRIMARY KEY(id)"
                  ");");

    addCommand(2,
               "CREATE TABLE `tareasEjecucionConstraints` ("
               "    `id`	INTEGER NOT NULL UNIQUE,"
               "    `idTask1`	INTEGER,"
               "    `idTask2`	INTEGER,"
               "    `type`	INTEGER,"
               "    `relationType`	INTEGER,"
               "    PRIMARY KEY(id)"
               ");");

    addCommand(2, "UPDATE version set versionInfo = 2;");
}


void ProjectUpdater::scriptsVersion3()
{
    addCommand(3, "ALTER TABLE tareasEjecucion ADD COLUMN `idCertificacion` INTEGER;");

    addCommand(3, "UPDATE version set versionInfo = 3;");

}
