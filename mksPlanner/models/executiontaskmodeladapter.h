#ifndef EXECUTIONTASKMODELADAPTER_H
#define EXECUTIONTASKMODELADAPTER_H

#include <QObject>
#include <QAbstractItemModel>
#include "models/executiontaskmodel.h"

class ExecutionTaskModelAdapter : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit ExecutionTaskModelAdapter(ExecutionTaskModel* model, QObject *parent = 0);

    virtual ~ExecutionTaskModelAdapter();

    /*reimp*/ int rowCount( const QModelIndex& idx ) const;
    /*reimp*/ int columnCount( const QModelIndex& idx ) const;

    /*reimp*/ QModelIndex index( int row, int col, const QModelIndex& parent = QModelIndex() ) const;
    QModelIndex index(int idTask);
    /*reimp*/ QModelIndex parent(const QModelIndex& child ) const;

    /*reimp*/QVariant headerData( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;
    /*reimp*/ QVariant data( const QModelIndex& idx, int role = Qt::DisplayRole ) const;
    /*reimp*/ bool setData( const QModelIndex& idx,  const QVariant& value,
                            int role = Qt::DisplayRole );

    /*reimp*/ bool insertRows( int row, int count, const QModelIndex& parent = QModelIndex() );
    bool removeRow(int row, const QModelIndex &parent);

    /*reimp*/ Qt::ItemFlags flags(const QModelIndex& idx) const;

    virtual void editEntity(int row);
    virtual void editEntity(QModelIndex index);
    void removeEntity(QWidget *parent, QModelIndex& index);
    bool canCreateEntity() const;

    EntityBasePtr itemByRowId(int row);

private:
    QModelIndex createIndex(int idTask, ExecutionTaskModel::Node *node);

signals:

public slots:
private:
    ExecutionTaskModel *_model;
};
#endif // EXECUTIONTASKMODELADAPTER_H
