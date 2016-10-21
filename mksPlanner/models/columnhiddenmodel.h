#ifndef COLUMNHIDDENMODEL_H
#define COLUMNHIDDENMODEL_H

#include <QObject>
#include <QAbstractTableModel>
#include "models/modelbase.h"

class ColumnHiddenModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit ColumnHiddenModel(IModel* model, QObject *parent = 0);
    virtual ~ColumnHiddenModel();

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    void addColumnToHide(int column);

protected:
    //int calculateColumn(int column) const;
    void setupVisibleColumns();

private:
    IModel *_model;
    QSet<int> _columnsHidden;
    QList<int> _columnsVisible;
};


#endif // COLUMNHIDDENMODEL_H
