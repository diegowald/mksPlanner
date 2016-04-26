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
    bool canBeSplitted(QModelIndex &index) const;
    void splitTask(QModelIndex &index);
    void splitTask(EntityBasePtr execTask, const QDate& fecha);


    EntityBasePtr itemByRowId(int row);

    int idFromPlanning(int idPlanningTask);

    void setProyecto(EntityBasePtr proyecto);

    IModel *innerModel() const;

    QSet<int> childIds(int idParent);

private:
    QModelIndex createIndex(int idTask, ExecutionTaskModel::Node *node);
    void splitTaskSplitted(ExecutionTaskModel::Node *node, bool useDialog, const QDate &date);
    void splitTaskNotSplitted(ExecutionTaskModel::Node *node, bool useDialog, const QDate &date);

signals:
private slots:
    void on_model_dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles);

public slots:
private:
    ExecutionTaskModel *_model;
    EntityBasePtr _proyecto;
};
#endif // EXECUTIONTASKMODELADAPTER_H
