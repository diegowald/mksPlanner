#ifndef TAREASPROVEEDORESMODEL_H
#define TAREASPROVEEDORESMODEL_H

#include <QObject>
#include "models/modelbase.h"

class RubrosProveedoresModel : public ModelBase
{
    Q_OBJECT
public:
    explicit RubrosProveedoresModel(QObject *parent = 0);
    //QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role);

    virtual void editEntity(int row);
    void setIdProveedor(int idProveedor);

    virtual EntityBasePtr getItemByRowid(int row);
    virtual EntityBasePtr getItemBy(int idRubro, int idProveedor);
protected:
    virtual QString _getSQLRead() const;
    virtual int _loadEntity(QSqlRecord record);
    virtual EntityBasePtr internalCreateEntity(int assignedId);

    virtual QVariant modelData(EntityBasePtr entity, int column, int role) const;
    virtual bool modelSetData(EntityBasePtr entity, int column, const QVariant &value, int role);
    virtual void defineColumnNames();
private:
    void classifyEntity(EntityBasePtr entity);
signals:

public slots:
private:
    int _idProveedor;
    QMap<int, QList<int>> _entityMappingByIdProveedor;
};

#endif // TAREASPROVEEDORESMODEL_H
