#include "tareasmodel.h"
#include "models/material.h"

TareasModel::TareasModel(QObject *parent) : MaterialesBaseModel(MaterialesBaseModel::FilterCriteria::OnlyTasks, parent)
{
}

EntityBasePtr TareasModel::internalCreateEntity(int assignedId)
{
    return MaterialPtr::create(assignedId);
}

