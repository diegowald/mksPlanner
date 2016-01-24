#ifndef PROVEEDORESMODEL_H
#define PROVEEDORESMODEL_H

#include <QObject>
#include "models/modelbase.h"

class ProveedoresModel : public ModelBase
{
    Q_OBJECT
public:
    explicit ProveedoresModel(QObject *parent = 0);
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;


    virtual void editEntity(int row);

protected:
    virtual QString _getSQLRead() const;
    virtual int _loadEntity(QSqlRecord record);
    virtual EntityBasePtr internalCreateEntity(int assignedId);
    virtual QVariant modelData(EntityBasePtr entity, int column, int role) const;
};

#endif // PROVEEDORESMODEL_H
