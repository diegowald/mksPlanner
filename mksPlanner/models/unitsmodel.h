#ifndef UNITSMODEL_H
#define UNITSMODEL_H

#include "models/modelbase.h"


class UnitsModel : public ModelBase
{
    Q_OBJECT
public:
    UnitsModel(QObject *parent = 0);
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    virtual QVariant modelData(EntityBasePtr entity, int column, int role = Qt::DisplayRole) const;

    virtual void editEntity(int row);

protected:
    virtual QString _getSQLRead() const;
    virtual int _loadEntity(QSqlRecord record);
    virtual EntityBasePtr internalCreateEntity(int assignedId);

signals:

public slots:

private:
};

#endif // UNITSMODEL_H
