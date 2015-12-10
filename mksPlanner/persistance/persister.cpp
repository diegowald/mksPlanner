#include "persister.h"
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>
#include <QSqlError>

PersisterBase::PersisterBase()
{
}

void PersisterBase::load(const QString &filename)
{
    _filename = filename;
    // Abro la base de datos
    connectToDatabase();

    // Obtengo el query para leer todos los registros
    QString sql = _getSQLRead();

    // ejecuto el query
    QSqlQuery query(_database);
    qDebug() << query.exec(sql);
    qDebug() << query.lastError().text();

    // cargo los registros.
    while (query.next())
    {
        _loadEntity(query.record());
    }
    // cierro la base de datos
    _database.close();
}

void PersisterBase::save(const QString &filename)
{
    _filename = filename;
    // Abro la base de datos
    connectToDatabase();

    // Obtengo los queries de eliminacion;
    QList<QSqlQuery*> queries = getQueries(_database);

    bool result = true;
    _database.transaction();
    foreach (QSqlQuery *query, queries)
    {
        if (!query->exec())
        {
            qDebug() << query->lastError().text();
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


bool PersisterBase::connectToDatabase()
{
    _database = QSqlDatabase::addDatabase("QSQLITE");
    //_database.setDatabaseName(":memory:");
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
