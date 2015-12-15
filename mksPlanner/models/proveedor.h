#ifndef PROVEEDOR_H
#define PROVEEDOR_H


#include <QObject>
#include "models/entitybase.h"

class Proveedor : public EntityBase
{
    Q_OBJECT
public:
    explicit Proveedor(int id);

    explicit Proveedor(int id, const QString &name, const QString &telefono);

    virtual bool internalSetData(const int column, const QVariant &value, int role);
    virtual QVariant internalData(const int column, int role = Qt::DisplayRole) const;

    virtual QSqlQuery* getQuery(QSqlDatabase &database);

    QString name() const;
    QString telefono() const;
signals:

public slots:

private:
    QString _name;
    QString _telefono;
};

typedef QSharedPointer<Proveedor> ProveedorPtr;

#endif // PROVEEDOR_H
