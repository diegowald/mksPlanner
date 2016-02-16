#ifndef MATERIAL_H
#define MATERIAL_H

#include <QObject>
#include "models/entitybase.h"

class Material : public EntityBase
{
    Q_OBJECT
public:
    explicit Material(int id, const QString &name, const QString &description, int idUnit, int idRubro);
    explicit Material(int id);
    //virtual bool internalSetData(const int column, const QVariant &value, int role);

    virtual QString toDebugString();


    virtual QSqlQuery* getQuery(QSqlDatabase &database);

    QString name() const;
    QString description() const;
    int idUnit() const;
    EntityBasePtr unit() const;
    int idRubro() const;
    EntityBasePtr rubro() const;

    bool isTask() const; // devuelve true si el rubro en el que esta es tarea

    void setName(const QString &value);
    void setDescription(const QString &value);
    void setUnit(int idUnit);
    void setRubro(int idRubro);

    QSet<int> materialsComposedBy();

    QMap<QString, double> listadoMaterialesCantidades(double cantidadARealizar);

    bool isCompuesto() const;

signals:

public slots:

private:
    QString _name;
    QString _description;
    int _idUnit;
    int _idRubro;
};

typedef QSharedPointer<Material> MaterialPtr;

#endif // MATERIAL_H
