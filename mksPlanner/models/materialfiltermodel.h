#ifndef MATERIALFILTERMODEL_H
#define MATERIALFILTERMODEL_H

#include <QAbstractTableModel>
#include <models/modelbase.h>


class MaterialFilterModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit MaterialFilterModel(ModelBase *model, bool filterByTask, QObject *parent = 0);

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    virtual int columnCount(const QModelIndex &parent) const;

    virtual EntityBasePtr getItemByRowid(int row);
private slots:
    void on_rowsInserted(const QModelIndex &parent, int first, int last);
    void on_rowsRemoved(const QModelIndex &parent, int first, int last);

signals:

public slots:

private:
    void classify();

    QList<int> _mapping;
    ModelBase *_model;
    bool _filterByTask;
};

#endif // MATERIALFILTERMODEL_H
