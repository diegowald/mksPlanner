#ifndef PERSISTER_H
#define PERSISTER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlRecord>

class PersisterBase
{
    Q_GADGET
public:
    explicit PersisterBase();

    void setFileName(const QString &filename);
    void load(const QString &filename);
    void save(const QString &filename);
    void setDBName(const QString &dbName);

    QString filename() const;

protected:
    bool connectToDatabase();

    virtual QString _getSQLRead() const = 0;
    virtual int _loadEntity(QSqlRecord record) = 0;
    virtual QList<QSqlQuery*> getQueries(QSqlDatabase &database) = 0;
    virtual void markAsSaved() = 0;
    virtual void postProcessData() = 0;
signals:

public slots:

private:
    QString _filename;
    QSqlDatabase _database;
    QString _dbName;
};

#endif // PERSISTER_H
