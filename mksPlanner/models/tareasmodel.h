#ifndef TAREASMODEL_H
#define TAREASMODEL_H

#include <QObject>
#include "models/materialesbasemodel.h"


class TareasModel : public IModel
{
    Q_OBJECT
public:
    explicit TareasModel(IModel* materiales, QObject *parent = 0);

    // QAbstractItemModel interface
public:
    virtual int rowCount(const QModelIndex &parent) const override;
    virtual int columnCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;

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
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    virtual QVariant data(const int id, const int column, int role) const override;
    virtual bool isDirty() const override;
    virtual bool implementsDelegate() const override;
    virtual QStyledItemDelegate *delegate() override;
    virtual bool canCreateEntity() const override;
    virtual EntityBasePtr createEntity() override;
    virtual void editEntity(int row) override;
    virtual void removeEntity(QWidget *parent, QModelIndex &index) override;
    virtual int columnIndex(const QString &name) const override;
    virtual int rowFromId(int id);
    virtual bool insertRows(int row, int count, const QModelIndex &parent);
    virtual void refreshData() override;

protected:
    virtual EntityBasePtr internalCreateEntity(int assignedId);

signals:

public slots:
private:
    void classify();
private:
    IModel *_model;
    QList<int> _mapping;
};

#endif // TAREASMODEL_H

