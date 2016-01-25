#ifndef COSTOMATERIALCOMPUESTO_H
#define COSTOMATERIALCOMPUESTO_H

#include <QObject>
#include <QObject>
#include "models/costomaterial.h"
#include <QDate>

class CostoMaterialCompuesto : public CostoMaterial
{
    Q_OBJECT
public:
    explicit CostoMaterialCompuesto(int id, int idMaterial);
    explicit CostoMaterialCompuesto(int id);

    //virtual bool internalSetData(const int column, const QVariant &value, int role);

    virtual QSqlQuery* getQuery(QSqlDatabase &database);

    virtual double costo() const;
    virtual QDate desde() const;
};

typedef QSharedPointer<CostoMaterialCompuesto> CostoMaterialCompuestoPtr;

#endif // COSTOMATERIALCOMPUESTO_H



