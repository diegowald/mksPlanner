#ifndef PLANNINGTASKMODELADAPTER_H
#define PLANNINGTASKMODELADAPTER_H

#include <QAbstractItemModel>
#include "models/planningtaskmodel.h"

class PlanningTaskModelAdapter : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit PlanningTaskModelAdapter(PlanningTaskModel *model, QObject *parent = 0);
    virtual ~PlanningTaskModelAdapter();

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

    void setProyecto(EntityBasePtr entity);

private:
    QModelIndex createIndex(int idTask, PlanningTaskModel::Node *node);

signals:

public slots:
private:
    PlanningTaskModel *_model;
    EntityBasePtr _proyecto;
};

#endif // PLANNINGTASKMODELADAPTER_H
