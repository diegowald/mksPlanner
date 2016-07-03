#ifndef COSTOMATERIALESMODEL_H
#define COSTOMATERIALESMODEL_H

#include <QObject>
#include "models/modelbase.h"
#include "models/costomaterial.h"
#include <QMultiMap>


class CostoMaterialesModel : public ModelBase
{
    Q_OBJECT
public:
    explicit CostoMaterialesModel(const QDate &fecha, QObject *parent = 0);
    //QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role);



    Qt::ItemFlags flags(const QModelIndex &index) const;

    virtual void editEntity(int row);
    void setIdMaterialPadre(int idMaterialPadre);

    virtual EntityBasePtr getItemByRowid(int row);
    virtual EntityBasePtr getItemByIdMaterial(int idMaterial);

    void setFecha(const QDate &fecha);

    QSet<int> compuestosPor(int idMaterial);
    QStyledItemDelegate *delegate();

protected:
    virtual QString _getSQLRead() const;
    virtual int _loadEntity(QSqlRecord record);
    virtual EntityBasePtr internalCreateEntity(int assignedId);
    virtual void postProcessData();
    virtual QVariant modelData(EntityBasePtr entity, int column, int role) const;
    virtual bool modelSetData(EntityBasePtr entity, int column, const QVariant &value, int role);
    virtual void defineColumnNames();

    void filtrarPorFecha();
    int buscarIdPorIdMaterial(int idMaterial);

private:
    CostoMaterialPtr cast(EntityBasePtr entity);


private:
    QMap<int, int> _mappingMaterialToCosto;
    QMultiMap<int, int> _costosPorMaterial;
    bool _crearMaterialCompuesto; // esta es una propiedad temporal que se utiliza para crear un nuevo elemento
    QDate _fecha; // fecha en la que se toma el costo/precio
};

#endif // COSTOMATERIALESMODEL_H

