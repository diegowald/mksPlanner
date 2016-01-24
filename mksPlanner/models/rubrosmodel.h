#ifndef RUBROSMODEL_H
#define RUBROSMODEL_H


#include "models/modelbase.h"

class RubrosModel : public ModelBase
{
    Q_OBJECT
public:
    explicit RubrosModel(QObject *parent = 0);

    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    virtual void editEntity(int row);

protected:
    virtual QString _getSQLRead() const;
    virtual int _loadEntity(QSqlRecord record);
    virtual EntityBasePtr internalCreateEntity(int assignedId);

    virtual QVariant modelData(EntityBasePtr entity, int column, int role) const;

signals:

public slots:

private:
};

#endif // RUBROSMODEL_H
