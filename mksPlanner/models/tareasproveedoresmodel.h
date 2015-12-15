#ifndef TAREASPROVEEDORESMODEL_H
#define TAREASPROVEEDORESMODEL_H

#include <QObject>
#include "models/modelbase.h"

class TareasProveedoresModel : public ModelBase
{
    Q_OBJECT
public:
    explicit TareasProveedoresModel(QObject *parent = 0);
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role);

    virtual void editEntity(int row);
    void setIdProveedor(int idProveedor);

    virtual EntityBasePtr getItemByRowid(int row);
protected:
    virtual QString _getSQLRead() const;
    virtual int _loadEntity(QSqlRecord record);
    virtual EntityBasePtr internalCreateEntity(int assignedId);

private:
    void classifyEntity(EntityBasePtr entity);
signals:

public slots:
private:
    int _idProveedor;
    QMap<int, QList<int>> _entityMappingByIdProveedor;
};

#endif // TAREASPROVEEDORESMODEL_H
