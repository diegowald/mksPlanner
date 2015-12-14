#ifndef TASKSMODEL_H
#define TASKSMODEL_H

#include <QObject>
#include "models/materialesbasemodel.h"

class TasksModel : public MaterialesBaseModel
{
    Q_OBJECT
public:
    explicit TasksModel(QObject *parent = 0);

protected:
    virtual EntityBasePtr internalCreateEntity(int assignedId);

signals:

public slots:
};

#endif // TASKSMODEL_H
