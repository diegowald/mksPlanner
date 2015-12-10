#include "materialslibrary.h"
#include "models/unitsmodel.h"
#include "models/materialesmodel.h"

MaterialsLibrary::MaterialsLibrary(QObject *parent) : LibraryBase(parent)
{
    addModel("unidades", new UnitsModel(this));
    addModel("materiales", new MaterialesModel(this));
    //addModel("componentesMateriales", new ComponentesMateriales(this));
}

void MaterialsLibrary::internalSaveTables(const QString &filename)
{
    model("unidades")->save(filename);
    model("materiales")->save(filename);
//    model("componentesMateriales")->save(filename);
}

void MaterialsLibrary::internalLoadTables(const QString &filename)
{
    model("unidades")->load(filename);
    model("materiales")->load(filename);
//    model("componentesMateriales")->load(filename);
}
