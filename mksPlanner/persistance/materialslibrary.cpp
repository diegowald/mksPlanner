#include "materialslibrary.h"
#include "models/unitsmodel.h"
#include "models/materialesmodel.h"
#include "models/componentesmateriales.h"
#include "models/proveedoresmodel.h"
#include "models/rubrosproveedoresmodel.h"
#include "models/rubrosmodel.h"
#include "persistance/materialesupdater.h"
#include "models/costomaterialesmodel.h"
#include "models/tareasmodel.h"

MaterialsLibrary::MaterialsLibrary(QObject *parent) : LibraryBase(parent)
{
    addModel(Tables::Unidades, new UnitsModel(this));
    addModel(Tables::MaterialesYTareas, new MaterialesBaseModel(this));
    addModel(Tables::Materiales, new MaterialesModel(model(Tables::MaterialesYTareas), this));
    addModel(Tables::Tareas, new TareasModel(model(Tables::MaterialesYTareas), this));
    addModel(Tables::ComponentesMateriales, new ComponentesMaterialesModel(this));
    addModel(Tables::Proveedores, new ProveedoresModel(this));
    addModel(Tables::Rubros, new RubrosModel(this));
    addModel(Tables::CostosUnitarios, new CostoMaterialesModel(this));
    addModel(Tables::RubrosProveedores, new RubrosProveedoresModel(this));
}

void MaterialsLibrary::internalSaveTables(const QString &filename)
{
    model(Tables::Unidades)->save(filename);
    model(Tables::MaterialesYTareas)->save(filename);
//    model(Tables::Materiales)->save(filename);
//    model(Tables::Tareas)->save(filename);
    model(Tables::ComponentesMateriales)->save(filename);
    model(Tables::Proveedores)->save(filename);
    model(Tables::Rubros)->save(filename);
    model(Tables::CostosUnitarios)->save(filename);
    model(Tables::RubrosProveedores)->save(filename);
}

void MaterialsLibrary::internalLoadTables(const QString &filename)
{
    model(Tables::Unidades)->load(filename);
    model(Tables::MaterialesYTareas)->load(filename);
    model(Tables::Proveedores)->load(filename);
    model(Tables::Rubros)->load(filename);
    model(Tables::RubrosProveedores)->load(filename);
    model(Tables::Materiales)->load(filename);
    model(Tables::Tareas)->load(filename);
    model(Tables::ComponentesMateriales)->load(filename);
    model(Tables::CostosUnitarios)->load(filename);
}

void MaterialsLibrary::updateFromVersion(const QString &filename, const QString &versionInfo)
{
    MaterialesUpdater updater;
    updater.updateFromVersion(filename, versionInfo.toInt());
}
