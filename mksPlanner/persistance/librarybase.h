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

    void save();
    void load();

protected:
    virtual void internalSaveTables() = 0;
    virtual void internalLoadTables() = 0;

    void addModel(const QString &name, ModelBasePtr model);
    ModelBasePtr model(const QString &name);

signals:

public slots:

private:
    QMap<QString, ModelBasePtr> _models;
};

#endif // LIBRARYBASE_H
