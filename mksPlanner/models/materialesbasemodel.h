#ifndef MATERIALESBASEMODEL_H
#define MATERIALESBASEMODEL_H

#include <QObject>
#include "models/modelbase.h"
#include "models/material.h"

class MaterialesBaseModel : public ModelBase
{
    Q_OBJECT
public:

    explicit MaterialesBaseModel(QObject *parent = 0);
    //QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    virtual void editEntity(int row);

protected:
    virtual QString _getSQLRead() const;
    virtual int _loadEntity(QSqlRecord record);
    virtual QVariant modelData(EntityBasePtr entity, int column, int role) const;
    virtual bool modelSetData(EntityBasePtr entity, int column, const QVariant &value, int role);
    void defineColumnNames();

    virtual EntityBasePtr internalCreateEntity(int assignedId) override;
signals:

public slots:

private:
    MaterialPtr cast(EntityBasePtr entity);
private:

};

#endif // MATERIALESBASEMODEL_H
