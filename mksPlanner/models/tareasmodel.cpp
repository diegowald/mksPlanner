#include "tareasmodel.h"
#include "models/material.h"
#include "views/dlgmaterialeditor.h"
#include <QMessageBox>

TareasModel::TareasModel(IModel *materiales, QObject *parent) : IModel(parent)
{
    _model = materiales;
    classify();
}

EntityBasePtr TareasModel::internalCreateEntity(int assignedId)
{
    return _model->createEntity();
}



int TareasModel::rowCount(const QModelIndex &parent) const
{
    return _mapping.count();
}

int TareasModel::columnCount(const QModelIndex &parent) const
{
    return _model->columnCount(parent);
}

QVariant TareasModel::data(const QModelIndex &index, int role) const
{
    if (index.isValid())
    {
        int id = _mapping.at(index.row());
        return _model->data(id, index.column(), role);
    }
    else
    {
        return QVariant();
    }
}

QString TareasModel::_getSQLRead() const
{
    return "";
}

int TareasModel::_loadEntity(QSqlRecord record)
{
    return -1;
}

QList<QSqlQuery *> TareasModel::getQueries(QSqlDatabase &database)
{
    return QList<QSqlQuery*>();
}

void TareasModel::markAsSaved()
{
}

void TareasModel::postProcessData()
{
    classify();
}

EntityBasePtr TareasModel::getItem(int id) const
{
    return _model->getItem(id);
}

EntityBasePtr TareasModel::getItemByRowid(int row) const
{
    return _model->getItem(_mapping.at(row));
}

QSet<int> TareasModel::ids() const
{
    return QSet<int>::fromList(_mapping);
}

QVariant TareasModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return _model->headerData(section, orientation, role);
}


QVariant TareasModel::data(const int id, const int column, int role) const
{
    return _model->data(id, column, role);
}

bool TareasModel::isDirty() const
{
    return _model->isDirty();
}

bool TareasModel::implementsDelegate() const
{
    return _model->implementsDelegate();
}

QStyledItemDelegate *TareasModel::delegate()
{
    return _model->delegate();
}

bool TareasModel::canCreateEntity() const
{
    return _model->canCreateEntity();
}

EntityBasePtr TareasModel::createEntity()
{
    return _model->createEntity();
}

void TareasModel::addEntity(EntityBasePtr entity)
{
    _model->addEntity(entity);
}

void TareasModel::editEntity(int row)
{
    int id = _mapping.at(row);

    dlgMaterialEditor dlg(dynamic_cast<MaterialesBaseModel*>(_model), _model->rowFromId(id), true);
    dlg.exec();
}

void TareasModel::removeEntity(QWidget *parent, QModelIndex &index)
{
    EntityBasePtr entity = getItemByRowid(index.row());
    if (QMessageBox::question(parent, "Confirmar borrar elemento", "Desea borrar el elemento?", QMessageBox::StandardButton::Yes, QMessageBox::No) == QMessageBox::Yes)
    {
        removeRow(index.row(), index.parent());
        removeEntity(entity->id());
    }
}

void TareasModel::removeEntity(int id)
{
/*    _model->removeEntity(id);
    _mapping.removeAt(_mapping.indexOf(id));*/
}

bool TareasModel::removeRow(int row, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row);
    _model->removeEntity(_mapping.at(row));
    _mapping.removeAt(row);
    endRemoveRows();
}
int TareasModel::columnIndex(const QString &name) const
{
    return _model->columnIndex(name);
}

int TareasModel::rowFromId(int id)
{
    return _mapping.indexOf(id);
}

bool TareasModel::insertRows(int row, int count, const QModelIndex &parent)
{
    bool success;

    beginInsertRows(parent, row, row + count - 1);
    for (int i = 0; i < count; ++i)
    {
        EntityBasePtr entity = createEntity();
        _mapping.append(entity->id());
    }
    success = true;
    endInsertRows();

    return success;
}

void TareasModel::classify()
{
    _mapping.clear();
    foreach (int id, _model->ids())
    {
        EntityBasePtr entity = _model->getItem(id);
        MaterialPtr mat = qSharedPointerDynamicCast<Material>(entity);
        if (mat->isTask())
        {
            _mapping.append(id);
        }
    }
}



void TareasModel::refreshData()
{
    classify();
}
