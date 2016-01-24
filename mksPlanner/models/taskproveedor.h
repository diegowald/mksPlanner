#ifndef TASKPROVEEDOR_H
#define TASKPROVEEDOR_H

#include "models/entitybase.h"

class TaskProveedor : public EntityBase
{
    Q_OBJECT
public:
    explicit TaskProveedor(int id, int idProveedor, int idTask);
    explicit TaskProveedor(int id);

    virtual bool internalSetData(const int column, const QVariant &value, int role);
    //virtual QVariant internalData(const int column, int role = Qt::DisplayRole) const;

    virtual QString toDebugString();
    virtual QSqlQuery* getQuery(QSqlDatabase &database);

    int idProveedor() const;
    EntityBasePtr proveedor() const;
    int idTask() const;
    EntityBasePtr task() const;

    void setIdProveedor(int id);
    void setIdTask(int id);
signals:

public slots:

private:
    int _idProveedor;
    int _idTask;
};

typedef QSharedPointer<TaskProveedor> TaskProveedorPtr;

#endif // TASKPROVEEDOR_H
