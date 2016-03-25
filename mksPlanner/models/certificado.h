#ifndef CERTIFICADO_H
#define CERTIFICADO_H

#include <QObject>
#include "models/entitybase.h"
#include <QDate>

// este es el certificado que se extiende al ciente o a cada proveedor.
class Certificado : public EntityBase
{
    Q_OBJECT
public:

    enum class StatusCertificado
    {
        enProceso,
        entregado,
        abonado
    };

    explicit Certificado(int id, int idCertificacion, int idProveedor, bool isClient,
                         StatusCertificado statusCertificado,
                         const QDate &fechaEmision,
                         const QDate &desde, const QDate &hasta);
    explicit Certificado(int id);

    virtual QString toDebugString();
    virtual QSqlQuery* getQuery(QSqlDatabase &database);

    int idCertificacion() const;
    int idProveedor() const;
    bool isClientCertificate() const;
    StatusCertificado statusCertificado() const;
    QDate fechaEmision() const;
    QDate desde() const;
    QDate hasta() const;
    QString cliente() const;
    QString proveedor() const;
    QString nroCertificado() const;

    void setIdCertificacion(int value);
    void setIdProveedor(int value);
    void setIsClientCertificate(bool value);
    void setStatusCertificado(StatusCertificado value);
    void setFechaEmision(const QDate& value);
    void setDesde(const QDate &value);
    void setHasta(const QDate &value);

    void setIdProyecto(int idProyecto);
signals:

public slots:

private:
    int _idCertificacion;
    int _idProveedor;
    bool _isClientCertificate;
    StatusCertificado _statusCertificado;

    QDate _fechaEmision;
    QDate _desde;
    QDate _hasta;

    int _idProyecto;

};

typedef QSharedPointer<Certificado> CertificadoPtr;

#endif // CERTIFICADO_H

