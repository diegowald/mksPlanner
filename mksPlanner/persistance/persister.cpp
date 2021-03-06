#include "persister.h"
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>
#include <QDebug>


PersisterBase::PersisterBase()
{
    _dbName = "";
}

void PersisterBase::load(const QString &filename)
{
    _filename = filename;
    connectToDatabase();

    QString sql = _getSQLRead();

    QSqlQuery query(_database);
    query.exec(sql);
    if (query.lastError().text() != " ")
        qDebug() << query.lastError().text();

    while (query.next())
    {
        _loadEntity(query.record());
    }
    _database.close();

    postProcessData();
}

void PersisterBase::save(const QString &filename)
{
    _filename = filename;
    connectToDatabase();

    QList<QSqlQuery*> queries = getQueries(_database);

    bool result = true;
    if (queries.count() > 0)
    {
        _database.transaction();
        foreach (QSqlQuery *query, queries)
        {
            qDebug() << query->executedQuery();
            qDebug() << query->boundValues();
            qDebug() << query->boundValues().count();
            if (!query->exec())
            {
                qDebug() << query->lastError().databaseText();
                qDebug() << query->lastError().text();
                qDebug() << query->lastError().driverText();
                qDebug() << query->lastError().nativeErrorCode();
                result = false;
                break;
            }
        }
        if (result)
        {
            _database.commit();
        }
        else
        {
            _database.rollback();
        }

        foreach (QSqlQuery *query, queries)
        {
            delete query;
        }
        queries.clear();
        markAsSaved();
    }
}


bool PersisterBase::connectToDatabase()
{
    if (!QSqlDatabase::database(_dbName).isValid())
    {
        _database = QSqlDatabase::addDatabase("QSQLITE", _dbName);
    }
    else
    {
        _database = QSqlDatabase::database(_dbName);
    }
    _database.setDatabaseName(_filename);
    if (!_database.open()) {
        QMessageBox::critical(0, "Cannot open database",
                              "Unable to establish a database connection.\n"
                              "This example needs SQLite support. Please read "
                              "the Qt SQL driver documentation for information how "
                              "to build it.\n\n"
                              "Click Cancel to exit.", QMessageBox::Cancel);
        return false;
    }
    return true;
}

void PersisterBase::setFileName(const QString &filename)
{
    _filename = filename;
}

void PersisterBase::setDBName(const QString &dbName)
{
    _dbName = dbName;
}

QString PersisterBase::filename() const
{
    return _filename;
}
