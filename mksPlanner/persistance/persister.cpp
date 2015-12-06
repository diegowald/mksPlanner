#include "persister.h"
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>
#include <QSqlError>

PersisterBase::PersisterBase(const QString &filename, QObject *parent)
{
    _filename = filename;
}

void PersisterBase::load()
{
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

void PersisterBase::save()
{
    // Abro la base de datos
    connectToDatabase();

    // Obtengo los queries de eliminacion;
    //QStringList sql = _getSQLToRemove();
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
