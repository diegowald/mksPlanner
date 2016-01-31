#ifndef COSTOMATERIAL_H
#define COSTOMATERIAL_H

#include <QObject>
#include "models/entitybase.h"
#include <QDate>

class CostoMaterial : public EntityBase
{
    Q_OBJECT
public:
    explicit CostoMaterial(int id, int idMaterial, double costo, double precio, QDate desde);
    explicit CostoMaterial(int id);

    //virtual bool internalSetData(const int column, const QVariant &value, int role);

    virtual QString toDebugString();

    virtual QSqlQuery* getQuery(QSqlDatabase &database);

    int idMaterial() const;
    EntityBasePtr material() const;
    virtual double costo() const;
    virtual double precio() const;
    virtual QDate desde() const;

    void setIdMaterial(int id);
    virtual void setCosto(double value);
    virtual void setPrecio(double value);
    virtual void setDesde(QDate &date);

signals:

public slots:

protected:
    int _idMaterial;
    double _costo;
    double _precio;
    QDate _desde;
};

typedef QSharedPointer<CostoMaterial> CostoMaterialPtr;


#endif // COSTOMATERIAL_H


