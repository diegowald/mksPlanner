#ifndef LIBRARYBASE_H
#define LIBRARYBASE_H

#include <QObject>
#include <QMap>
#include "models/modelbase.h"

class LibraryBase : public QObject
{
    Q_OBJECT
public:
    explicit LibraryBase(QObject *parent = 0);

    void save(const QString &filename);
    void load(const QString &filename);
    ModelBase* model(const QString &name);

protected:
    virtual void internalSaveTables(const QString &filename) = 0;
    virtual void internalLoadTables(const QString &filename) = 0;

    void addModel(const QString &name, ModelBase* model);


signals:

public slots:

private:
    QMap<QString, ModelBase*> _models;
};

#endif // LIBRARYBASE_H
