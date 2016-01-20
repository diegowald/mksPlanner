#ifndef MATERIAL_H
#define MATERIAL_H

#include <QObject>
#include "models/entitybase.h"

class Material : public EntityBase
{
    Q_OBJECT
public:
    explicit Material(int id, const QString &name, const QString &description, int idUnit, bool isUsableMaterial, bool isTask);
    explicit Material(int id, bool isTask);
    virtual bool internalSetData(const int column, const QVariant &value, int role);
    virtual QVariant internalData(const int column, int role = Qt::DisplayRole) const;

    virtual QString toDebugString();


    virtual QSqlQuery* getQuery(QSqlDatabase &database);

    QString name() const;
    QString desription() const;
    int idUnit() const;
    EntityBasePtr unit() const;

    bool isTask() const;

    void setUnit(int idUnit);

    QSet<int> materialsComposedBy();

signals:

public slots:

private:
    QString _name;
    QString _description;
    int _idUnit;
    bool _isUsableMaterial;
    // bool isUsableMaterial: true, para poder usarlo como material en tareas, por ejemplo mamposteroa
    // bool isUsableMaterial: false, es un material para ser usado por otros materiales, como por ejemplo cemento portland
    bool _isTask; // true, si es tarea.
};

typedef QSharedPointer<Material> MaterialPtr;

#endif // MATERIAL_H
