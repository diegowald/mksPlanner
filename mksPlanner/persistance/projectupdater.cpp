#include "projectupdater.h"


ProjectUpdater::ProjectUpdater(QObject *parent) : Updater(parent)
{
    scriptsVersion1();
    scriptsVersion2();
    scriptsVersion3();
    scriptsVersion4();
    scriptsVersion5();
    scriptsVersion6();
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

    addCommand(3, " CREATE TABLE `certificaciones` ( "
                  " `id`	INTEGER NOT NULL UNIQUE, "
                  " `fechaCertificacion`	TEXT NOT NULL, "
                  " `certificacionStatus`	INTEGER, "
                  " PRIMARY KEY(id) "
                  ");");

    addCommand(3, "CREATE TABLE `tareasCertificados` ( "
                  " `id`	INTEGER NOT NULL UNIQUE, "
                  " `idCertificacion`	INTEGER NOT NULL, "
                  " `idProveedor`	INTEGER NOT NULL, "
                  " `idTareaEjecucion`	INTEGER NOT NULL, "
                  " PRIMARY KEY(id) "
                  " );");

    addCommand(3, "CREATE TABLE `certificados` ( "
                  " `id`	INTEGER NOT NULL UNIQUE, "
                  " `idCertificacion`	INTEGER NOT NULL, "
                  " `idProveedor`	INTEGER NOT NULL, "
                  " `statusCertificado`	INTEGER, "
                  " `fechaEmision`	INTEGER, "
                  " `desde`	TEXT, "
                  " `hasta`	TEXT, "
                  " `fechaPago`	TEXT, "
                  " PRIMARY KEY(id) "
                  " ); ");

    addCommand(3, "UPDATE version set versionInfo = 3;");
}

void ProjectUpdater::scriptsVersion4()
{
    addCommand(4, "ALTER TABLE tareasEjecucion ADD COLUMN `isSplittedPart` INTEGER;");
    addCommand(4, "ALTER TABLE tareasEjecucion ADD COLUMN `idTareaPlanificada` INTEGER;");
    addCommand(4, "ALTER TABLE certificados ADD COLUMN `fechaPago` TEXT;");

    addCommand(4, "UPDATE version set versionInfo = 4;");
}


void ProjectUpdater::scriptsVersion5()
{
    addCommand(5, "ALTER TABLE tareasEjecucion ADD COLUMN `cantidadRealizada` NUMBER;");

    addCommand(5, "UPDATE version set versionInfo = 5;");
}


void ProjectUpdater::scriptsVersion6()
{
    addCommand(6, "ALTER TABLE proyectos ADD COLUMN `idTipoDeObra` NUMBER;");

    addCommand(6, "UPDATE version set versionInfo = 6;");
}
