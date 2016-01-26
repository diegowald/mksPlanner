#include "updater.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>



Updater::Updater(QObject *parent) : QObject(parent)
{

}

void Updater::updateFromVersion(const QString &filename, const int version)
{
    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(filename);
    if (database.open())
    {
        QPair<int, QString> element;
        foreach (element, _commands)
        {
            if (version < element.first)
            {
                executeCommand(database, element.second);
            }
        }
        database.close();
    }
}

void Updater::executeCommand(QSqlDatabase &database, const QString &sqlCommand)
{
    QSqlQuery query(database);
    //qDebug() << sqlCommand;
    //qDebug() << query.exec(sqlCommand);
    //qDebug() << query.lastError().text();
}

void Updater::addCommand(int version, const QString &command)
{
    QPair<int, QString> cmd(version, command);
    _commands.append(cmd);
}
