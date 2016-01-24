#ifndef COSTOMATERIALCOMPUESTO_H
#define COSTOMATERIALCOMPUESTO_H

#include <QObject>
#include <QObject>
#include "models/costomaterial.h"
#include <QDate>

class CostoMaterialCompuesto : public EntityBase
{
    Q_OBJECT
public:
    explicit CostoMaterialCompuesto(int id, int idMaterial);
    explicit CostoMaterialCompuesto(int id);

    virtual bool internalSetData(const int column, const QVariant &value, int role);
    virtual QVariant internalData(const int column, int role = Qt::DisplayRole) const;

    virtual QSqlQuery* getQuery(QSqlDatabase &database);

    virtual QString toDebugString();

    virtual double costo() const;
    virtual QDate desde() const;

    void setIdMaterial(int id);

private:
    int _idMaterial;
};

typedef QSharedPointer<CostoMaterialCompuesto> CostoMaterialCompuestoPtr;

#endif // COSTOMATERIALCOMPUESTO_H



