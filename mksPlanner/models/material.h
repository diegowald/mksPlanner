#ifndef MATERIAL_H
#define MATERIAL_H

#include <QObject>
#include "models/entitybase.h"

class Material : public EntityBase
{
    Q_OBJECT
public:
    explicit Material(int id, const QString &name, const QString &description, int idUnit, int idRubro, bool isUsableMaterial, bool isTask);
    explicit Material(int id, bool isTask);
    //virtual bool internalSetData(const int column, const QVariant &value, int role);

    virtual QString toDebugString();


    virtual QSqlQuery* getQuery(QSqlDatabase &database);

    QString name() const;
    QString description() const;
    int idUnit() const;
    EntityBasePtr unit() const;
    int idRubro() const;
    EntityBasePtr rubro() const;

    bool isTask() const;

    void setName(const QString &value);
    void setDescription(const QString &value);
    void setUnit(int idUnit);
    void setRubro(int idRubro);

    QSet<int> materialsComposedBy();

    bool isCompuesto() const;
    bool isUsableMaterial() const;

signals:

public slots:

private:
    QString _name;
    QString _description;
    int _idUnit;
    int _idRubro;
    bool _isUsableMaterial;
    // bool isUsableMaterial: true, para poder usarlo como material en tareas, por ejemplo mamposteroa
    // bool isUsableMaterial: false, es un material para ser usado por otros materiales, como por ejemplo cemento portland
    bool _isTask; // true, si es tarea.
};

typedef QSharedPointer<Material> MaterialPtr;

#endif // MATERIAL_H
