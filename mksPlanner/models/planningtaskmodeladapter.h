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
    /*reimp*/ QModelIndex parent( const QModelIndex& idx ) const;

    /*reimp*/QVariant headerData( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;
    /*reimp*/ QVariant data( const QModelIndex& idx, int role = Qt::DisplayRole ) const;
    /*reimp*/ bool setData( const QModelIndex& idx,  const QVariant& value,
                            int role = Qt::DisplayRole );

    /*reimp*/ bool insertRows( int row, int count, const QModelIndex& parent = QModelIndex() );

    /*reimp*/ Qt::ItemFlags flags(const QModelIndex& idx) const;

    virtual void editEntity(int row);
    void removeEntity(QWidget *parent, int row);
    bool canCreateEntity() const;
signals:

public slots:
private:
    PlanningTaskModel *_model;
};

#endif // PLANNINGTASKMODELADAPTER_H
