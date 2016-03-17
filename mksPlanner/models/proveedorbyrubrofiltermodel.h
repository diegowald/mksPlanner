#ifndef PROVEEDORBYRUBROFILTERMODEL_H
#define PROVEEDORBYRUBROFILTERMODEL_H

#include <QAbstractTableModel>
#include "models/modelbase.h"

class ProveedorByRubroFilterModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit ProveedorByRubroFilterModel(IModel* model, int idRubro, QObject *parent = 0);

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    virtual int columnCount(const QModelIndex &parent) const;

    virtual EntityBasePtr getItemByRowid(int row);
    void setIdRubro(int idRubro);
public slots:

signals:

public slots:

private:
    void classify();

    QList<int> _mapping;
    IModel *_model;
    int _idRubro;
};

#endif // PROVEEDORBYRUBROFILTERMODEL_H

