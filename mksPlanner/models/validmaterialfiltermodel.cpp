#include "validmaterialfiltermodel.h"
#include "models/componentematerial.h"
#include "models/material.h"
#include <QSet>

ValidMaterialFilterModel::ValidMaterialFilterModel(int idMaterial, ModelBase *model, QObject *parent) : QAbstractTableModel(parent)
{
    _model = model;
    _idMaterial = idMaterial;
    classify();
}


void ValidMaterialFilterModel::classify()
{
    _mapping.clear();

    EntityBasePtr entity = _model->getItem(_idMaterial);
    MaterialPtr material = qSharedPointerDynamicCast<Material>(entity);
    QSet<int> exclusion = material->materialsComposedBy();
    QSet<int> materiales = _model->ids();
    materiales = materiales.subtract(exclusion);
    materiales.remove(_idMaterial);
    QList<int> lst = materiales.toList();

    _mapping = materiales.toList();
}

int ValidMaterialFilterModel::rowCount(const QModelIndex &) const
{
    return _mapping.count();
}

QVariant ValidMaterialFilterModel::data(const QModelIndex &index, int role) const
{
    int id = _mapping.at(index.row());
    return _model->data(id, index.column(), role);
}

int ValidMaterialFilterModel::columnCount(const QModelIndex &) const
{
    return _model->columnCount();
}


EntityBasePtr ValidMaterialFilterModel::getItemByRowid(int row)
{
    int id = _mapping.at(row);
    //qDebug() << "row: " << row << ", id: " << id;
    EntityBasePtr entity = _model->getItem(id);
    //qDebug() << "entity: " << entity->toDebugString();
    return entity;
}
