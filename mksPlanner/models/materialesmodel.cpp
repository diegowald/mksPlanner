#include "materialesmodel.h"
#include "models/material.h"

MaterialesModel::MaterialesModel(QObject *parent) : MaterialesBaseModel(MaterialesBaseModel::FilterCriteria::OnlyMaterials, parent)
{

}

EntityBasePtr MaterialesModel::internalCreateEntity(int assignedId)
{
    return MaterialPtr::create(assignedId);
}

