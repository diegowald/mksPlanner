#include "librarybase.h"
#include <QDebug>
#include <QSqlError>

LibraryBase::LibraryBase(QObject *parent) : QObject(parent)
{

}

void LibraryBase::setFileName(const QString &filename)
{
    _filename = filename;
}

void LibraryBase::load()
{
    checkVersion(_filename);
    internalLoadTables(_filename);
}

void LibraryBase::save()
{
    internalSaveTables(_filename);
}

bool LibraryBase::isDirty() const
{
    foreach(ModelBase *model, _models.values())
    {
        if (model->isDirty())
            return true;
    }
    return false;
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
    query.exec(sql);
    qDebug() << query.lastError().text();

    QString versionInfo = "";
    while (query.next())
    {
        versionInfo = query.record().value("versionInfo").toString();
    }

    //qDebug() << versionInfo;
    updateFromVersion(filename, versionInfo);
    database.close();
}

