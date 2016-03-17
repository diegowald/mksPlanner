#include "librarybase.h"
#include <QSqlError>
#include <QDebug>

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
    foreach(IModel *model, _models.values())
    {
        if (model->isDirty())
            return true;
    }
    return false;
}

void LibraryBase::addModel(Tables name, IModel *model)
{
    _models[name] = model;
    connect(static_cast<ModelBase*>(model), &ModelBase::changed, this, &LibraryBase::on_changed);
}

IModel *LibraryBase::model(Tables name)
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

void LibraryBase::on_changed(Tables table)
{
    emit dataChanged(table);
}
