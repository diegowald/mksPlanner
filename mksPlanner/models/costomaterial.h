#ifndef COSTOMATERIAL_H
#define COSTOMATERIAL_H

#include <QObject>
#include "models/entitybase.h"
#include <QDate>

class CostoMaterial : public EntityBase
{
    Q_OBJECT
public:
    explicit CostoMaterial(int id, int idMaterial, double costo, QDate desde);
    explicit CostoMaterial(int id);

    virtual bool internalSetData(const int column, const QVariant &value, int role);
    virtual QVariant internalData(const int column, int role = Qt::DisplayRole) const;

    virtual QString toDebugString();

    virtual QSqlQuery* getQuery(QSqlDatabase &database);

    int idMaterial() const;
    EntityBasePtr material() const;
    double costo() const;
    QDate desde() const;

    void setIdMaterial(int id);
    void setCosto(double value);
    void setDesde(QDate &date);

signals:

public slots:

private:
    int _idMaterial;
    double _costo;
    QDate _desde;
};

typedef QSharedPointer<CostoMaterial> CostoMaterialPtr;


#endif // COSTOMATERIAL_H


