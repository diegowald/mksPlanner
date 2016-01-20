#include "librarybase.h"
#include <QDebug>
#include <QSqlError>

LibraryBase::LibraryBase(QObject *parent) : QObject(parent)
{

}

void LibraryBase::load(const QString &filename)
{
    checkVersion(filename);
    internalLoadTables(filename);
}

void LibraryBase::save(const QString &filename)
{
    internalSaveTables(filename);
}

void LibraryBase::addModel(Tables name, ModelBase* model)
{
    _models[name] = model;
}

ModelBase *LibraryBase::model(Tables name)
{
    return _models[name];
}

void LibraryBase::checkVersion(const QString &filename)
{
    QString sql = "select versionInfo from version";
    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
    //_database.setDatabaseName(":memory:");
    database.setDatabaseName(filename);
    if (!database.open()) {
        /*QMessageBox::critical(0, "Cannot open database",
                              "Unable to establish a database connection.\n"
                              "This example needs SQLite support. Please read "
                              "the Qt SQL driver documentation for information how "
                              "to build it.\n\n"
                              "Click Cancel to exit.", QMessageBox::Cancel);*/
        return;
    }

    QSqlQuery query(database);
    qDebug() << query.exec(sql);
    qDebug() << query.lastError().text();

    // cargo los registros.
    QString versionInfo = "";
    while (query.next())
    {
        versionInfo = query.record().value("versionInfo").toString();
    }

    qDebug() << versionInfo;
    updateFromVersion(filename, versionInfo);
    // cierro la base de datos
    database.close();
}
