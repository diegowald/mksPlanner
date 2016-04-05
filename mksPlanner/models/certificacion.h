#ifndef CERTIFICACION_H
#define CERTIFICACION_H

#include <QObject>
#include "models/entitybase.h"
#include <QDate>


class Certificacion : public EntityBase
{
    Q_OBJECT
public:
    enum class CertificacionStatus
    {
        Preparacion,
        Emitido
    };

    explicit Certificacion(int id, const QDate &fechaCertificacion, CertificacionStatus certificacionStatus);
    explicit Certificacion(int id);


    virtual QString toDebugString();
    virtual QSqlQuery* getQuery(QSqlDatabase &database);

    QDate fechaCertificacion() const;
    CertificacionStatus certificacionStatus() const;

    void setFechaCertificacion(const QDate &value);
    void setCertificacionStatus(CertificacionStatus value);

signals:

public slots:

private:
    QDate _fechaCertificacion;
    CertificacionStatus _certificacionStatus;
};

typedef QSharedPointer<Certificacion> CertificacionPtr;

#endif // CERTIFICACION_H
