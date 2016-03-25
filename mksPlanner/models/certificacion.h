#ifndef CERTIFICACION_H
#define CERTIFICACION_H

#include <QObject>
#include "models/entitybase.h"
#include <QDateTime>


class Certificacion : public EntityBase
{
    Q_OBJECT
public:
    explicit Certificacion(int id, const QDateTime &fechaCertificacion);
    explicit Certificacion(int id);


    virtual QString toDebugString();
    virtual QSqlQuery* getQuery(QSqlDatabase &database);

    QDateTime fechaCertificacion() const;

    void setFechaCertificacion(const QDateTime &value);
signals:

public slots:

private:
    QDateTime _fechaCertificacion;
};

typedef QSharedPointer<Certificacion> CertificacionPtr;

#endif // CERTIFICACION_H
