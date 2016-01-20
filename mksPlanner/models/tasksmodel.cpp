#include "tasksmodel.h"
#include "models/material.h"

TasksModel::TasksModel(QObject *parent) : MaterialesBaseModel(true, parent)
{
}

EntityBasePtr TasksModel::internalCreateEntity(int assignedId)
{
    return MaterialPtr::create(assignedId, true);
}