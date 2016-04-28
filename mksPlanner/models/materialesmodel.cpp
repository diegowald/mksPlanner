#include "materialesmodel.h"
#include "models/material.h"
#include "views/dlgmaterialeditor.h"
#include <QMessageBox>



MaterialesModel::MaterialesModel(IModel *materiales, QObject *parent) : IModel(parent)
{
    _model = materiales;
    classify();
}

EntityBasePtr MaterialesModel::internalCreateEntity(int assignedId)
{
    return _model->createEntity();
}



int MaterialesModel::rowCount(const QModelIndex &parent) const
{
    return _mapping.count();
}

int MaterialesModel::columnCount(const QModelIndex &parent) const
{
    return _model->columnCount(parent);
}

QVariant MaterialesModel::data(const QModelIndex &index, int role) const
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

QString MaterialesModel::_getSQLRead() const
{
    return "";
}

int MaterialesModel::_loadEntity(QSqlRecord record)
{
    return -1;
}

QList<QSqlQuery *> MaterialesModel::getQueries(QSqlDatabase &database)
{
    return QList<QSqlQuery*>();
}

void MaterialesModel::markAsSaved()
{
}

void MaterialesModel::postProcessData()
{
    classify();
}

EntityBasePtr MaterialesModel::getItem(int id) const
{
    return _model->getItem(id);
}

EntityBasePtr MaterialesModel::getItemByRowid(int row) const
{
    return _model->getItem(_mapping.at(row));
}

QSet<int> MaterialesModel::ids() const
{
    return QSet<int>::fromList(_mapping);
}

QVariant MaterialesModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return _model->headerData(section, orientation, role);
}

QVariant MaterialesModel::data(const int id, const int column, int role) const
{
    return _model->data(id, column, role);
}

bool MaterialesModel::isDirty() const
{
    return _model->isDirty();
}

bool MaterialesModel::implementsDelegate() const
{
    return _model->implementsDelegate();
}

QStyledItemDelegate *MaterialesModel::delegate()
{
    return _model->delegate();
}

bool MaterialesModel::canCreateEntity() const
{
    return _model->canCreateEntity();
}

EntityBasePtr MaterialesModel::createEntity()
{
    return _model->createEntity();
}

void MaterialesModel::addEntity(EntityBasePtr entity)
{
    _model->addEntity(entity);
}

void MaterialesModel::editEntity(int row)
{
    int id = _mapping.at(row);

    dlgMaterialEditor dlg(dynamic_cast<MaterialesBaseModel*>(_model), _model->rowFromId(id), false);
    dlg.exec();
}

void MaterialesModel::removeEntity(QWidget *parent, QModelIndex &index)
{
    EntityBasePtr entity = getItemByRowid(index.row());
    if (QMessageBox::question(parent, "Confirmar borrar elemento", "Desea borrar el elemento?", QMessageBox::StandardButton::Yes, QMessageBox::No) == QMessageBox::Yes)
    {
        removeRow(index.row(), index.parent());
        removeEntity(entity->id());
    }
}

void MaterialesModel::removeEntity(int id)
{
    /*_model->removeEntity(id);
    _mapping.removeAt(_mapping.indexOf(id));
*/}


bool MaterialesModel::removeRow(int row, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row);
    _model->removeEntity(_mapping.at(row));
    _mapping.removeAt(row);
    endRemoveRows();
}

int MaterialesModel::columnIndex(const QString &name) const
{
    return _model->columnIndex(name);
}

int MaterialesModel::rowFromId(int id)
{
    return _mapping.indexOf(id);
}

bool MaterialesModel::insertRows(int row, int count, const QModelIndex &parent)
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

void MaterialesModel::classify()
{
    _mapping.clear();
    foreach (int id, _model->ids())
    {
        EntityBasePtr entity = _model->getItem(id);
        MaterialPtr mat = qSharedPointerDynamicCast<Material>(entity);
        if (!mat->isTask())
        {
            _mapping.append(id);
        }
    }
}



void MaterialesModel::refreshData()
{
    classify();
}
