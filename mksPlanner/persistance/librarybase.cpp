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
    database.setDatabaseName(filename);
    if (!database.open())
    {
        return;
    }

    QSqlQuery query(database);
    qDebug() << query.exec(sql);
    qDebug() << query.lastError().text();

    QString versionInfo = "";
    while (query.next())
    {
        versionInfo = query.record().value("versionInfo").toString();
    }

    qDebug() << versionInfo;
    updateFromVersion(filename, versionInfo);
    database.close();
}
