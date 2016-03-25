#ifndef CERTIFICACIONESMODEL_H
#define CERTIFICACIONESMODEL_H

#include "models/modelbase.h"
#include "models/certificacion.h"

class CertificacionesModel : public ModelBase
{
    Q_OBJECT
public:
    explicit CertificacionesModel(int idProyecto, QObject *parent = 0);

    virtual void editEntity(int row);
    int idCertificacionProxima(const QDateTime &fecha) const;

protected:
    virtual QString _getSQLRead() const;
    virtual int _loadEntity(QSqlRecord record);
    virtual EntityBasePtr internalCreateEntity(int assignedId);

    virtual void defineColumnNames();

    CertificacionPtr cast(EntityBasePtr entity);



signals:

public slots:
private:
    int _idProyecto;
};

#endif // CERTIFICACIONESMODEL_H
