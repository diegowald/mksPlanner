#include "materialfiltermodel.h"
#include "models/rubro.h"
#include "models/material.h"
#include "globalcontainer.h"

MaterialFilterModel::MaterialFilterModel(IModel *model, bool filterByTask, QObject *parent) : QAbstractTableModel(parent)
{
    _model = model;
    _filterByTask = filterByTask;
    connect(model, &ModelBase::rowsInserted, this, &MaterialFilterModel::on_rowsInserted);
    connect(model, &ModelBase::rowsRemoved, this, &MaterialFilterModel::on_rowsRemoved);
    classify();
}

void MaterialFilterModel::classify()
{
    _mapping.clear();

    int materialCount = _model->rowCount(createIndex(0,0));

    for (int i = 0; i < materialCount; ++i)
    {
        MaterialPtr material = qSharedPointerDynamicCast<Material>(_model->getItemByRowid(i));
        if (_filterByTask)
        {
            if (material->isTask())
                _mapping.append(material->id());
        }
        else
        {
            if (!material->isTask())
                _mapping.append(material->id());
        }
    }
}

int MaterialFilterModel::rowCount(const QModelIndex &) const
{
    return _mapping.count();
}

QVariant MaterialFilterModel::data(const QModelIndex &index, int role) const
{
    int id = _mapping.at(index.row());
    return _model->data(id, index.column(), role);
}

int MaterialFilterModel::columnCount(const QModelIndex &) const
{
    return _model->columnCount();
}


EntityBasePtr MaterialFilterModel::getItemByRowid(int row)
{
    int id = _mapping.at(row);
    //qDebug() << "row: " << row << ", id: " << id;
    EntityBasePtr entity = _model->getItem(id);
    //qDebug() << "entity: " << entity->toDebugString();
    return entity;
}

void MaterialFilterModel::on_rowsInserted(const QModelIndex &, int, int)
{
    classify();
}


void MaterialFilterModel::on_rowsRemoved(const QModelIndex &, int, int)
{
    classify();
}
