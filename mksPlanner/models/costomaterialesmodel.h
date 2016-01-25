#ifndef COSTOMATERIALESMODEL_H
#define COSTOMATERIALESMODEL_H

#include <QObject>
#include "models/modelbase.h"

class CostoMaterialesModel : public ModelBase
{
    Q_OBJECT
public:
    explicit CostoMaterialesModel(QObject *parent = 0);
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role);

    Qt::ItemFlags flags(const QModelIndex &index) const;

    virtual void editEntity(int row);
    void setIdMaterialPadre(int idMaterialPadre);

    virtual EntityBasePtr getItemByRowid(int row);
    virtual EntityBasePtr getItemByIdMaterial(int idMaterial);

    QSet<int> compuestosPor(int idMaterial);
    QStyledItemDelegate *delegate();

protected:
    virtual QString _getSQLRead() const;
    virtual int _loadEntity(QSqlRecord record);
    virtual EntityBasePtr internalCreateEntity(int assignedId);
    virtual void postProcessData();
    virtual QVariant modelData(EntityBasePtr entity, int column, int role) const;
    virtual bool modelSetData(EntityBasePtr entity, int column, const QVariant &value, int role);

private:
    QMap<int, int> _mappingMaterialToCosto;
    bool _crearMaterialCompuesto; // esta es una propiedad temporal que se utiliza para crear un nuevo elemento
};

#endif // COSTOMATERIALESMODEL_H

