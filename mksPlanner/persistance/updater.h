#ifndef UPDATER_H
#define UPDATER_H

#include <QObject>
#include <QPair>
#include <QSqlDatabase>


class Updater : public QObject
{
    Q_OBJECT
public:
    explicit Updater(QObject *parent = 0);

    void updateFromVersion(const QString &filename, const int version);

    void executeCommand(QSqlDatabase &database, const QString &sqlCommand);

protected:
    void addCommand(int version, const QString &command);

signals:

public slots:
private:
    QList<QPair<int, QString> > _commands;

};

#endif // UPDATER_H
