#include "materialslibrary.h"
#include "models/unitsmodel.h"
#include "models/materialesmodel.h"
#include "models/componentesmateriales.h"
#include "models/tasksmodel.h"
#include "models/proveedoresmodel.h"
#include "models/tareasproveedoresmodel.h"

MaterialsLibrary::MaterialsLibrary(QObject *parent) : LibraryBase(parent)
{
    addModel(Tables::Unidades, new UnitsModel(this));
    addModel(Tables::Materiales, new MaterialesModel(this));
    addModel(Tables::ComponentesMateriales, new ComponentesMaterialesModel(this));
    addModel(Tables::Tareas, new TasksModel(this));
    addModel(Tables::Proveedores, new ProveedoresModel(this));
    addModel(Tables::TareasProveedores, new TareasProveedoresModel(this));
}

void MaterialsLibrary::internalSaveTables(const QString &filename)
{
    model(Tables::Unidades)->save(filename);
    model(Tables::Materiales)->save(filename);
    model(Tables::ComponentesMateriales)->save(filename);
    model(Tables::Tareas)->save(filename);
    model(Tables::Proveedores)->save(filename);
    model(Tables::TareasProveedores)->save(filename);
}

void MaterialsLibrary::internalLoadTables(const QString &filename)
{
    model(Tables::Unidades)->load(filename);
    model(Tables::Materiales)->load(filename);
    model(Tables::ComponentesMateriales)->load(filename);
    model(Tables::Tareas)->load(filename);
    model(Tables::Proveedores)->load(filename);
    model(Tables::TareasProveedores)->load(filename);
}
