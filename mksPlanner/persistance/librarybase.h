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
    Rubros,
    Proyectos,
    CostosUnitarios,
    RubrosProveedores,
    PlanningTasks
};

class LibraryBase : public QObject
{
    Q_OBJECT
public:
    explicit LibraryBase(QObject *parent = 0);

    void setFileName(const QString &filename);
    void save();
    void load();
    ModelBase* model(Tables name);
    bool isDirty() const;

protected:
    virtual void internalSaveTables(const QString &filename) = 0;
    virtual void internalLoadTables(const QString &filename) = 0;
    virtual void updateFromVersion(const QString &filename, const QString &versionInfo) = 0;

    void addModel(Tables name, ModelBase* model);

private:
    void checkVersion(const QString &filename);
signals:

public slots:

private:
    QMap<Tables, ModelBase*> _models;
    QString _filename;
};

#endif // LIBRARYBASE_H
