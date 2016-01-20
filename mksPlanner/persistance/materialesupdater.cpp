#include "materialesupdater.h"

MaterialesUpdater::MaterialesUpdater(QObject *parent) : Updater(parent)
{
    addCommand(1, "CREATE TABLE `version` (`versionInfo` INTEGER);");
    addCommand(1, "ALTER TABLE materiales RENAME TO materialesOld;");
    addCommand(1, "CREATE TABLE `materiales` ( "
                                             " `id`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, "
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

    addCommand(1, "INSERT into version (versionInfo) VALUES (1)");
}
