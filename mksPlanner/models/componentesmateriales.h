#ifndef COMPONENTESMATERIALES_H
#define COMPONENTESMATERIALES_H

#include <QObject>
#include "models/modelbase.h"

class ComponentesMaterialesModel : public ModelBase
{
    Q_OBJECT
public:
    explicit ComponentesMaterialesModel(QObject *parent = 0);
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    virtual void editEntity(int row);
    void setIdMaterialPadre(int idMaterialPadre);
protected:
    virtual QString _getSQLRead() const;
    virtual void _loadEntity(QSqlRecord record);
    virtual EntityBasePtr internalCreateEntity(int assignedId);

signals:

public slots:
private:
    int _idMterialPadre;
};

#endif // COMPONENTESMATERIALES_H
