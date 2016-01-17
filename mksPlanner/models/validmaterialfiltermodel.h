#ifndef VALIDMATERIALFILTERMODEL_H
#define VALIDMATERIALFILTERMODEL_H

#include "models/modelbase.h"

class ValidMaterialFilterModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit ValidMaterialFilterModel(int idMaterial, ModelBase *model, QObject *parent = 0);
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    virtual int columnCount(const QModelIndex &parent) const;

    virtual EntityBasePtr getItemByRowid(int row);
public slots:

signals:

public slots:

private:
    void classify();

    QList<int> _mapping;
    ModelBase *_model;
    int _idMaterial;
};

#endif // VALIDMATERIALFILTERMODEL_H
