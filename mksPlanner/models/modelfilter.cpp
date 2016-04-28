#include "modelfilter.h"

ModelFilter::ModelFilter(IModel* model, FilterFunctor filter, QObject *parent) : IModel(parent)
{
    _model = model;
    _filter = filter;
    classify();
    connect(_model, &IModel::dataChanged, this, &ModelFilter::on_dataChanged);
}

void ModelFilter::on_dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles)
{
    classify();
}

void ModelFilter::classify()
{
    _mapping.clear();
    foreach (int id, _model->ids())
    {
        EntityBasePtr entity = _model->getItem(id);
        if (_filter(entity))
        {
            _mapping.append(id);
        }
    }
}


int ModelFilter::rowCount(const QModelIndex &parent) const
{
    return _mapping.count();
}

int ModelFilter::columnCount(const QModelIndex &parent) const
{
    return _model->columnCount(parent);
}

QVariant ModelFilter::data(const QModelIndex &index, int role) const
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

QString ModelFilter::_getSQLRead() const
{
    return "";
}

int ModelFilter::_loadEntity(QSqlRecord record)
{
    return -1;
}

QList<QSqlQuery *> ModelFilter::getQueries(QSqlDatabase &database)
{
    return QList<QSqlQuery*>();
}

void ModelFilter::markAsSaved()
{
}

void ModelFilter::postProcessData()
{
    classify();
}

EntityBasePtr ModelFilter::getItem(int id) const
{
    return _model->getItem(id);
}

EntityBasePtr ModelFilter::getItemByRowid(int row) const
{
    return _model->getItem(_mapping.at(row));
}

QSet<int> ModelFilter::ids() const
{
    return QSet<int>::fromList(_mapping);
}

QVariant ModelFilter::headerData(int section, Qt::Orientation orientation, int role) const
{
    return _model->headerData(section, orientation, role);
}


QVariant ModelFilter::data(const int id, const int column, int role) const
{
    return _model->data(id, column, role);
}

bool ModelFilter::isDirty() const
{
    return _model->isDirty();
}

bool ModelFilter::implementsDelegate() const
{
    return _model->implementsDelegate();
}

QStyledItemDelegate *ModelFilter::delegate()
{
    return _model->delegate();
}

bool ModelFilter::canCreateEntity() const
{
    return _model->canCreateEntity();
}

EntityBasePtr ModelFilter::createEntity()
{
    return _model->createEntity();
}

void ModelFilter::addEntity(EntityBasePtr entity)
{
    _model->addEntity(entity);
    classify();
}

void ModelFilter::editEntity(int row)
{
    int id = _mapping.at(row);
    return _model->editEntity(_model->rowFromId(id));
}

void ModelFilter::removeEntity(QWidget *parent, QModelIndex &index)
{
    _model->removeEntity(parent, index);
}

void ModelFilter::removeEntity(int id)
{
    _model->removeEntity(id);
}

int ModelFilter::columnIndex(const QString &name) const
{
    return _model->columnIndex(name);
}

int ModelFilter::rowFromId(int id)
{
    return _mapping.indexOf(id);
}

bool ModelFilter::insertRows(int row, int count, const QModelIndex &parent)
{
    bool success;

    beginInsertRows(parent, row, row + count - 1);
    for (int i = 0; i < count; ++i)
    {
        EntityBasePtr entity = createEntity();
    }
    success = true;
    endInsertRows();

    return success;
}


void ModelFilter::refreshData()
{
    classify();
    emit dataChanged(createIndex(0, 0), createIndex(rowCount(QModelIndex()), columnCount(QModelIndex())));
    emit layoutChanged();
}
