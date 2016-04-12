#ifndef TAREASCERTIFICADO_H
#define TAREASCERTIFICADO_H

#include "models/entitybase.h"
#include <QObject>
#include <QDate>

class TareaCertificado : public EntityBase
{
    Q_OBJECT
public:
    explicit TareaCertificado(int id, int idCertificacion, int idProveedor, int idTareaEjecucion);
    explicit TareaCertificado(int id);

    virtual QString toDebugString();
    virtual QSqlQuery* getQuery(QSqlDatabase &database);

    int idCertificacion() const;
    int idProveedor() const;
    int idTareaEjecucion() const;
    QString proveedor() const;
    EntityBasePtr tareaEjecucion() const;

    void setIdCertificacion(int value);
    void setIdProveedor(int value);
    void setIdTareaEjecucion(int value);

    void setIdProyecto(int idProyecto);
signals:

public slots:

private:
    int _idCertificacion;
    int _idProveedor;
    int _idTareaEjecucion;

    int _idProyecto;
};

typedef QSharedPointer<TareaCertificado> TareaCertificadoPtr;

#endif // TAREASCERTIFICADO_H




