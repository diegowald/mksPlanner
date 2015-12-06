#ifndef PERSISTER_H
#define PERSISTER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlRecord>

class PersisterBase
{
    Q_GADGET
public:
    explicit PersisterBase(const QString &filename, QObject *parent = 0);
    void load();
    void save();

protected:
    bool connectToDatabase();

    virtual QString _getSQLRead() const = 0;
    virtual void _loadEntity(QSqlRecord record) = 0;

signals:

public slots:

private:
    QString _filename;
    QSqlDatabase _database;
};

#endif // PERSISTER_H
