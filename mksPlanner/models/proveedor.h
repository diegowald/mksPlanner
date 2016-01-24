#ifndef PROVEEDOR_H
#define PROVEEDOR_H


#include <QObject>
#include "models/entitybase.h"

class Proveedor : public EntityBase
{
    Q_OBJECT
public:
    explicit Proveedor(int id);

    explicit Proveedor(int id, const QString &name, const QString &contacto,
                       const QString &email, const QString &telefono, const QString &direccion);

    virtual bool internalSetData(const int column, const QVariant &value, int role);

    virtual QString toDebugString();

    virtual QSqlQuery* getQuery(QSqlDatabase &database);

    QString name() const;
    QString contacto() const;
    QString email() const;
    QString telefono() const;
    QString direccion() const;
signals:

public slots:

private:
    QString _name;
    QString _contacto;
    QString _email;
    QString _telefono;
    QString _direccion;
};

typedef QSharedPointer<Proveedor> ProveedorPtr;

#endif // PROVEEDOR_H
