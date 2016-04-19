#ifndef CERTTIFICADOSMODEL_H
#define CERTTIFICADOSMODEL_H

#include "models/modelbase.h"
#include "models/certificado.h"

class CertificadosModel : public ModelBase
{
    Q_OBJECT
public:
    explicit CertificadosModel(int idProyecto, QObject *parent = 0);

    virtual void editEntity(int row);
    EntityBasePtr getItemByCertificacionIdProveedorId(int idCertificacion, int idProveedor);
    CertificadoPtr cast(EntityBasePtr entity);

protected:
    virtual QString _getSQLRead() const;
    virtual int _loadEntity(QSqlRecord record);
    virtual EntityBasePtr internalCreateEntity(int assignedId);

    virtual void defineColumnNames();


signals:

public slots:
private:
    int _idProyecto;
};

#endif // CERTTIFICADOSMODEL_H

