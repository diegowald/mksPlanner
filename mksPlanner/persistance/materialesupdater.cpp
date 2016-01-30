#include "materialesupdater.h"

MaterialesUpdater::MaterialesUpdater(QObject *parent) : Updater(parent)
{
    scriptsVersion1();
    scriptsVersion2();
}


void MaterialesUpdater::scriptsVersion1()
{
    addCommand(1, "CREATE TABLE `version` (`versionInfo` INTEGER);");
    addCommand(1, "ALTER TABLE materiales RENAME TO materialesOld;");
    addCommand(1, "CREATE TABLE `materiales` ( "
                                             " `id`	INTEGER NOT NULL PRIMARY KEY, "
                                             " `name`	TEXT NOT NULL, "
                                             " `description`	TEXT, "
                                             " `idUnit`	INTEGER, "
                                             " `idRubro` INTEGER, "
                                             " `isUsableMaterial`	INTEGER, "
                                             " `isTask`	INTEGER "
                                         " ); ");
    addCommand(1, "INSERT INTO materiales (id, name, description, idUnit, idRubro, isUsableMaterial, isTask) "
                                            " SELECT id, name, description, idUnit, 0, isUsableMaterial, isTask FROM materialesOld;");
    addCommand(1, "DROP TABLE materialesOld;");

    addCommand(1, " CREATE TABLE `rubros` ( "
                   " `id`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE, "
                   " `nombre`	TEXT NOT NULL, "
                   " `descripcion`	TEXT NOT NULL, "
                   " `isTask`	INTEGER "
               " ); ");

    addCommand(1,     "CREATE TABLE `costosMateriales` ( "
                      "    `id`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE, "
                      "    `idMaterial`	INTEGER NOT NULL, "
                      "    `costo`	REAL NOT NULL, "
                      "    `desde`	TEXT "
                      " ); ");

    addCommand(1, "DROP TABLE `tareasProveedores`;");

    addCommand(1, "CREATE TABLE `rubrosProveedores` ( "
                  "    `id`	INTEGER NOT NULL UNIQUE, "
                  "    `idProveedor`	INTEGER NOT NULL, "
                  "    `idRubro`	INTEGER NOT NULL, "
                  "    PRIMARY KEY(id) "
                  "); ");


    addCommand(1, "INSERT into version (versionInfo) VALUES (1)");
}


void MaterialesUpdater::scriptsVersion2()
{
    addCommand(2, "UPDATE version set versionInfo = 2;");
}
