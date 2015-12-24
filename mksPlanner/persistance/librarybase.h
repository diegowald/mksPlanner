#ifndef LIBRARYBASE_H
#define LIBRARYBASE_H

#include <QObject>
#include <QMap>
#include "models/modelbase.h"

enum class Tables {
    Unidades,
    Materiales,
    ComponentesMateriales,
    Tareas,
    Proveedores,
    TareasProveedores,
    Proyectos
};

class LibraryBase : public QObject
{
    Q_OBJECT
public:
    explicit LibraryBase(QObject *parent = 0);

    void save(const QString &filename);
    void load(const QString &filename);
    ModelBase* model(Tables name);

protected:
    virtual void internalSaveTables(const QString &filename) = 0;
    virtual void internalLoadTables(const QString &filename) = 0;

    void addModel(Tables name, ModelBase* model);


signals:

public slots:

private:
    QMap<Tables, ModelBase*> _models;
};

#endif // LIBRARYBASE_H
