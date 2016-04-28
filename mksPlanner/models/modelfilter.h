#ifndef MODELFILTER_H
#define MODELFILTER_H

#include <QObject>
#include <functional>
#include "models/modelbase.h"

typedef std::function<bool (EntityBasePtr)> FilterFunctor;

class ModelFilter : public IModel
{
    Q_OBJECT
public:
    explicit ModelFilter(IModel* model, FilterFunctor filter, QObject *parent = 0);

signals:

public slots:


    // QAbstractItemModel interface
public:
    virtual int rowCount(const QModelIndex &parent) const override;
    virtual int columnCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    // PersisterBase interface
protected:
    virtual QString _getSQLRead() const override;
    virtual int _loadEntity(QSqlRecord record) override;
    virtual QList<QSqlQuery *> getQueries(QSqlDatabase &database) override;
    virtual void markAsSaved() override;
    virtual void postProcessData() override;

    // IModel interface
public:
    virtual EntityBasePtr getItem(int id) const override;
    virtual EntityBasePtr getItemByRowid(int row) const override;
    virtual QSet<int> ids() const override;
    virtual QVariant data(const int id, const int column, int role) const override;
    virtual bool isDirty() const override;
    virtual bool implementsDelegate() const override;
    virtual QStyledItemDelegate *delegate() override;
    virtual bool canCreateEntity() const override;
    virtual EntityBasePtr createEntity() override;
    virtual void addEntity(EntityBasePtr entity) override;
    virtual void editEntity(int row) override;
    virtual void removeEntity(QWidget *parent, QModelIndex &index) override;
    virtual void removeEntity(int id) override;
    virtual int columnIndex(const QString &name) const override;
    virtual int rowFromId(int id) override;
    virtual bool insertRows(int row, int count, const QModelIndex &parent);
    virtual void refreshData() override;

private:
    void classify();

private slots:
    void on_dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles);

private:
    IModel *_model;
    FilterFunctor _filter;
    QList<int> _mapping;
};

#endif // MODELFILTER_H
