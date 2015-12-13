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

    virtual void editEntity(int row);

protected:
    virtual QString _getSQLRead() const;
    virtual void _loadEntity(QSqlRecord record);
    virtual EntityBasePtr createEntity();

signals:

public slots:

private:
};

#endif // UNITSMODEL_H
