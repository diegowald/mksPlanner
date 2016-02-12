#include "modelbase.h"
#include <QDebug>
#include "globalcontainer.h"
#include <QMessageBox>
#include <QAbstractTableModel>
#include "globalcontainer.h"

ModelBase::ModelBase(Tables tableType, const QString &counterName, bool implementsDelegate, const QString &dbName, QObject *parent) :
    PersisterBase(),
    QAbstractTableModel(parent)
{
    _counterName = counterName;
    _implementsDelegate = implementsDelegate;
    setDBName(dbName);
    setField(0, "id");
    defineColumnNames();
    _tableType = tableType;
    connect(this, &ModelBase::dataChanged, this, &ModelBase::on_dataChanged);
}

int ModelBase::rowCount(const QModelIndex &/*parent*/) const
{
    return _entityMapping.count();
}

QVariant ModelBase::data(const QModelIndex &index, int role) const
{
    if (index.isValid())
    {
        EntityBasePtr entity = _entities[_entityMapping.at(index.row())];
        return modelData(entity, index.column(), role);
    }
    else
    {
        return QVariant();
    }
}

QVariant ModelBase::data(const int id, const int column, int role) const
{
    return modelData(_entities[id], column, role);
}

bool ModelBase::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role == Qt::EditRole)
    {
        EntityBasePtr entity = _entities[_entityMapping.at(index.row())];
        bool result = modelSetData(entity, index.column(), value, role);
        if (result)
        {
            QModelIndex index0 = createIndex(index.row(), 0);
            QModelIndex index1 = createIndex(index.row(), columnCount() - 1);
            emit dataChanged(index0, index1);
        }
    }
    return true;
}

Qt::ItemFlags ModelBase::flags(const QModelIndex &index) const
{
    return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}


bool ModelBase::insertRows(int row, int count, const QModelIndex &parent)
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


bool ModelBase::removeRow(int row, const QModelIndex &parent)
{
    _entities[_entityMapping.at(row)]->deleteEntity();
    _entityMapping.removeAt(row);
}



QList<QSqlQuery*> ModelBase::getQueries(QSqlDatabase &database)
{
    QList<QSqlQuery*> queries;
    foreach (EntityBasePtr entity, _entities.values())
    {
        QSqlQuery* query = entity->getQuery(database);
        if (query != NULL)
        {
            queries.append(query);
        }
    }
    return queries;
}

void ModelBase::markAsSaved()
{
    foreach (EntityBasePtr entity, _entities.values())
    {
        if (entity->status() == EntityStatus::deleted)
        {
            _entities.remove(entity->id());
        }
        else
        {
            entity->updateStatus(EntityStatus::unchanged);
        }
    }
}

void ModelBase::addEntity(EntityBasePtr entity)
{
    _entities[entity->id()] = entity;
    _entityMapping.append(entity->id());
    int maxId = GlobalContainer::instance().counter(_counterName);
    maxId = (maxId < entity->id()) ? entity->id() : maxId;
    GlobalContainer::instance().setCounter(_counterName, maxId);
}

EntityBasePtr ModelBase::createEntity()
{
    if (canCreateEntity())
    {
        int maxId = GlobalContainer::instance().counter(_counterName);
        if (maxId == -1)
            maxId = 0;
        maxId++;
        EntityBasePtr entity = internalCreateEntity(maxId);
        GlobalContainer::instance().setCounter(_counterName, maxId);
        _entities[entity->id()] = entity;
        _entityMapping.append(entity->id());
        return entity;
    }
    else
    {
        return EntityBasePtr();
    }
}

void ModelBase::removeEntity(QWidget *parent, int row)
{
    EntityBasePtr entity = getItemByRowid(row);
    if (QMessageBox::question(parent, "Confirmar borrar elemento", "Desea borrar el elemento?", QMessageBox::StandardButton::Yes, QMessageBox::No) == QMessageBox::Yes)
    {
        removeRow(row, QModelIndex());
    }
}

EntityBasePtr ModelBase::getItem(int id)
{
    if (_entities.contains(id))
    {
        return _entities[id];
    }
    else
        return EntityBasePtr();
}

EntityBasePtr ModelBase::getItemByRowid(int row)
{
    /*qDebug() << row;
    qDebug() << _entityMapping.contains(row);
    if (_entityMapping.contains(row))
        qDebug() << _entityMapping[row];*/
    return getItem(_entityMapping[row]);
}

void ModelBase::setModified()
{
    QModelIndex idx;
    emit dataChanged(idx, idx);
}

QSet<int> ModelBase::ids()
{
    return QSet<int>::fromList(_entities.keys());
}

bool ModelBase::implementsDelegate() const
{
    return _implementsDelegate;
}

QStyledItemDelegate *ModelBase::delegate()
{
    return NULL;
}

void ModelBase::postProcessData()
{
}

void ModelBase::setField(int pos, const QString &fieldName)
{
    _fields[pos] = fieldName;
}

QString ModelBase::field(int pos)
{
    return _fields.contains(pos) ? _fields[pos] : "";
}

int ModelBase::columnIndex(const QString &name) const
{
    foreach (int key, _fields.keys())
    {
        if (_fields[key] == name)
            return key;
    }
    return -1;
}

int ModelBase::columnCount(const QModelIndex &parent) const
{
    return _fields.count();
}

QVariant ModelBase::headerData(int section, Qt::Orientation orientation, int role) const
{
    QVariant value = QVariant();
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal)
        {
            value = _fields.contains(section) ? _fields[section] : QVariant();
        }
    }
    else
    {
        value = QAbstractItemModel::headerData(section, orientation, role);
    }
    return value;
}

bool ModelBase::isDirty() const
{
    foreach (EntityBasePtr entity, _entities.values())
    {
        if (entity->isDirty())
            return true;
    }
    return false;
}

QList<EntityBasePtr> ModelBase::entities() const
{
    return _entities.values();
}

bool ModelBase::canCreateEntity() const
{
    foreach (int dependencyCode, _dependantTables)
    {
        Tables table = static_cast<Tables>(dependencyCode);
        if (GlobalContainer::instance().library()->model(table)->rowCount(QModelIndex()) == 0)
            return false;
    }
    return true;
}

void ModelBase::addDependency(int dependencyCode)
{
    _dependantTables << dependencyCode;
}

Tables ModelBase::tableType() const
{
    return _tableType;
}

void ModelBase::on_dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles)
{
    emit changed(_tableType);
}
