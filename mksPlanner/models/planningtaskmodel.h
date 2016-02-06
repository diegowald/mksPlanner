#ifndef PLANNINGTASKMODEL_H
#define PLANNINGTASKMODEL_H

#include <QObject>
#include "models/modelbase.h"

class PlanningTaskModel : public ModelBase
{
    Q_OBJECT
public:
    explicit PlanningTaskModel(int idProyecto, QObject *parent = 0);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    virtual void editEntity(int row);
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;

    virtual EntityBasePtr createEntity();

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

#endif // PLANNINGTASKMODEL_H
