#ifndef COMPONENTEMATERIAL_H
#define COMPONENTEMATERIAL_H

#include <QObject>
#include "models/entitybase.h"

class ComponenteMaterial : public EntityBase
{
    Q_OBJECT
public:
    explicit ComponenteMaterial(int id, int idMaterialPadre, int idMaterial, double cantidad);
    explicit ComponenteMaterial(int id);

    virtual bool internalSetData(const int column, const QVariant &value, int role);
    virtual QVariant internalData(const int column, int role = Qt::DisplayRole) const;

    virtual QSqlQuery* getQuery(QSqlDatabase &database);

    int idMaterialPadre() const;
    EntityBasePtr materialPadre() const;
    int idMaterial() const;
    EntityBasePtr material() const;
    double cantidad() const;

    void setIdMaterialPadre(int id);
    void setIdMaterial(int id);
    void setCantidad(double value);
signals:

public slots:

private:
    int _idMaterialPadre;
    int _idMaterial;
    double _cantidad;
};

typedef QSharedPointer<ComponenteMaterial> ComponenteMaterialPtr;

#endif // COMPONENTEMATERIAL_H
