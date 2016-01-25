#ifndef TASKPROVEEDOR_H
#define TASKPROVEEDOR_H

#include "models/entitybase.h"

class RubroProveedor : public EntityBase
{
    Q_OBJECT
public:
    explicit RubroProveedor(int id, int idProveedor, int idRubro);
    explicit RubroProveedor(int id);

    //virtual bool internalSetData(const int column, const QVariant &value, int role);

    virtual QString toDebugString();
    virtual QSqlQuery* getQuery(QSqlDatabase &database);

    int idProveedor() const;
    EntityBasePtr proveedor() const;
    int idRubro() const;
    EntityBasePtr rubro() const;

    void setIdProveedor(int id);
    void setIdRubro(int id);
signals:

public slots:

private:
    int _idProveedor;
    int _idRubro;
};

typedef QSharedPointer<RubroProveedor> RubroProveedorPtr;

#endif // TASKPROVEEDOR_H
