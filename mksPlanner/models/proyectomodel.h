#ifndef PROYECTOMODEL_H
#define PROYECTOMODEL_H

#include <QObject>
#include "models/modelbase.h"

class ProyectoModel : public ModelBase
{
    Q_OBJECT
public:
    explicit ProyectoModel(int idProyecto, QObject *parent = 0);
    //QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    virtual void editEntity(int row);

protected:
    virtual QString _getSQLRead() const;
    virtual int _loadEntity(QSqlRecord record);
    virtual EntityBasePtr internalCreateEntity(int assignedId);
    virtual QVariant modelData(EntityBasePtr entity, int column, int role) const;
    virtual bool modelSetData(EntityBasePtr entity, int column, const QVariant &value, int role);
    virtual void defineColumnNames();

private:
    int _idProyecto;
};

#endif // PROYECTOMODEL_H
