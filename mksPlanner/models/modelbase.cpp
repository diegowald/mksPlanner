#include "modelbase.h"
#include "globalcontainer.h"
#include <QMessageBox>
#include <QAbstractTableModel>
#include "globalcontainer.h"

IModel::IModel(QObject *parent) :
    PersisterBase(),
    QAbstractTableModel(parent)
{
}

ModelBase::ModelBase(Tables tableType, const QString &counterName, bool implementsDelegate, const QString &dbName, QObject *parent) :
    IModel(parent)
{
    _counterName = counterName;
    _implementsDelegate = implementsDelegate;
    setDBName(dbName);
    //setField(0, "id");
    setField(0, "id",
             [&] (EntityBasePtr entity, int role) -> QVariant
    {
        switch (role)
        {
        case Qt::DisplayRole:
        case Qt::EditRole:
            return entity->id();
            break;
        default:
            return QVariant();
            break;
        }
    }
    );
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
        if (_fields2.contains(index.column()))
            return _fields2[index.column()]->get(entity, role);
        /*else
            return modelData(entity, index.column(), role);*/
    }
    return QVariant();
}

QVariant ModelBase::data(const int id, const int column, int role) const
{
    if (_fields2.contains(column))
        return _fields2[column]->get(_entities[id], role);
    else
        return QVariant();
    //return modelData(_entities[id], column, role);
}

bool ModelBase::setData(const QModelIndex &index, const QVariant &value, int role)
{
    bool result = false;
    if (role == Qt::EditRole)
    {
        EntityBasePtr entity = _entities[_entityMapping.at(index.row())];
        result = _fields2[index.column()]->set(entity, value, role);
        //result = modelSetData(entity, index.column(), value, role);
        if (result)
        {
            QModelIndex index0 = createIndex(index.row(), 0);
            QModelIndex index1 = createIndex(index.row(), columnCount() - 1);
            emit dataChanged(index0, index1);
        }
    }
    return result;
}

Qt::ItemFlags ModelBase::flags(const QModelIndex &) const
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
    beginRemoveRows(parent, row, row);
    _entities[_entityMapping.at(row)]->deleteEntity();
    _entityMapping.removeAt(row);
    return true;
    endRemoveRows();
}

bool ModelBase::removeById(int id)
{
    int row = _entityMapping.indexOf(id);
    return removeRow(row, QModelIndex());
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

void ModelBase::removeEntity(QWidget *parent, QModelIndex &index)
{
    EntityBasePtr entity = getItemByRowid(index.row());
    if (QMessageBox::question(parent, "Confirmar borrar elemento", "Desea borrar el elemento?", QMessageBox::StandardButton::Yes, QMessageBox::No) == QMessageBox::Yes)
    {
        removeRow(index.row(), index.parent());
    }
}

EntityBasePtr ModelBase::getItem(int id) const
{
    if (_entities.contains(id))
    {
        return _entities[id];
    }
    else
        return EntityBasePtr();
}

EntityBasePtr ModelBase::getItemByRowid(int row) const
{
    /*qDebug() << row;
    qDebug() << _entityMapping.contains(row);
    if (_entityMapping.contains(row))
        qDebug() << _entityMapping[row];*/
    if (row == -1)
        return EntityBasePtr();
    else
        return getItem(_entityMapping[row]);
}

int ModelBase::rowFromId(int id)
{
    return _entityMapping.indexOf(id);
}

void ModelBase::setModified()
{
    QModelIndex idx;
    emit dataChanged(idx, idx);
}

QSet<int> ModelBase::ids() const
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

/*void ModelBase::setField(int pos, const QString &fieldName)
{
    _fields[pos] = fieldName;
}*/

void ModelBase::setField(int pos, const QString &fieldName,
                         std::function<QVariant (EntityBasePtr, int)> getter,
                         std::function<bool (EntityBasePtr, const QVariant&, int)> setter)
{
    FieldBehaviourPtr fb = FieldBehaviourPtr::create(fieldName, getter, setter);
    _fields2[pos] = fb;
}

void ModelBase::setField(int pos, const QString &fieldName,
                         std::function<QVariant (EntityBasePtr, int)> getter)
{
    FieldBehaviourPtr fb = FieldBehaviourPtr::create(fieldName, getter);
    _fields2[pos] = fb;
}

QString ModelBase::field(int pos)
{
    //return _fields.contains(pos) ? _fields[pos] : "";
    return _fields2.contains(pos) ? _fields2[pos]->name() : "";
}

int ModelBase::columnIndex(const QString &name) const
{
    foreach (int key, _fields2.keys())
    {
        if (_fields2[key]->name() == name)
            return key;
    }
    return -1;
}

int ModelBase::columnCount(const QModelIndex &) const
{
    return _fields2.count();
}

QVariant ModelBase::headerData(int section, Qt::Orientation orientation, int role) const
{
    QVariant value = QVariant();
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal)
        {
            value = _fields2.contains(section) ? _fields2[section]->name() : QVariant();
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

void ModelBase::on_dataChanged(const QModelIndex &, const QModelIndex &, const QVector<int> &)
{
    emit changed(_tableType);
}

void ModelBase::refreshData()
{
    emit changed(_tableType);
}
