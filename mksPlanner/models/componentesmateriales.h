#ifndef COMPONENTESMATERIALES_H
#define COMPONENTESMATERIALES_H

#include <QObject>
#include "models/modelbase.h"
#include "models/componentematerial.h"


class ComponentesMaterialesModel : public ModelBase
{
    Q_OBJECT
public:
    explicit ComponentesMaterialesModel(QObject *parent = 0);
    //QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role);

    virtual void editEntity(int row);
    void setIdMaterialPadre(int idMaterialPadre);

    virtual EntityBasePtr getItemByRowid(int row);

    QSet<int> compuestosPor(int idMaterial);

    QList<int> idComponentes(int idMaterialPadre) const;

protected:
    virtual QString _getSQLRead() const;
    virtual int _loadEntity(QSqlRecord record);
    virtual EntityBasePtr internalCreateEntity(int assignedId);
    virtual QVariant modelData(EntityBasePtr entity, int column, int role) const;
    virtual bool modelSetData(EntityBasePtr entity, int column, const QVariant &value, int role);
    virtual void defineColumnNames();

private:
    void classifyEntity(EntityBasePtr entity);
    ComponenteMaterialPtr cast(EntityBasePtr entity);
signals:

public slots:
private:
    int _idMterialPadre;
    QMap<int, QList<int>> _entityMappingByIdMaterialPadre;
};

#endif // COMPONENTESMATERIALES_H
