#include "proveedorbyrubrofiltermodel.h"
#include "models/proveedor.h"

ProveedorByRubroFilterModel::ProveedorByRubroFilterModel(ModelBase* model, int idRubro, QObject *parent) : QAbstractTableModel(parent)
{
    _model = model;
    setIdRubro(idRubro);
}

void ProveedorByRubroFilterModel::classify()
{
    _mapping.clear();

    int proveedoresCount = _model->rowCount(createIndex(0,0));

    for (int i = 0; i < proveedoresCount; ++i)
    {
        ProveedorPtr proveedor = qSharedPointerDynamicCast<Proveedor>(_model->getItemByRowid(i));
        if (proveedor->proveeRubro(_idRubro))
            _mapping.append(proveedor->id());
    }
}

int ProveedorByRubroFilterModel::rowCount(const QModelIndex &) const
{
    return _mapping.count();
}

QVariant ProveedorByRubroFilterModel::data(const QModelIndex &index, int role) const
{
    if (index.isValid() && _mapping.count() > 0)
    {
        int id = _mapping.at(index.row());
        return _model->data(id, index.column(), role);
    }
    else
    {
        return QVariant();
    }
}

int ProveedorByRubroFilterModel::columnCount(const QModelIndex &) const
{
    return _model->columnCount();
}

EntityBasePtr ProveedorByRubroFilterModel::getItemByRowid(int row)
{
    int id = _mapping.at(row);
    //qDebug() << "row: " << row << ", id: " << id;
    EntityBasePtr entity = _model->getItem(id);
    //qDebug() << "entity: " << entity->toDebugString();
    return entity;
}

void ProveedorByRubroFilterModel::setIdRubro(int idRubro)
{
    _mapping.clear();
    _idRubro = idRubro;
    classify();
}
