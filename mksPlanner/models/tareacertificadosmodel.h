#ifndef TAREACERTIFICADOSMODEL_H
#define TAREACERTIFICADOSMODEL_H

#include "models/modelbase.h"
#include "models/tareascertificado.h"

class TareaCertificadosModel : public ModelBase
{
    Q_OBJECT
public:
    explicit TareaCertificadosModel(int idProyecto, QObject *parent = 0);

    virtual void editEntity(int row);

    protected:
    virtual QString _getSQLRead() const;
    virtual int _loadEntity(QSqlRecord record);
    virtual EntityBasePtr internalCreateEntity(int assignedId);

    virtual void defineColumnNames();

    TareaCertificadoPtr cast(EntityBasePtr entity);

signals:

public slots:
private:
    int _idProyecto;

};

#endif // TAREACERTIFICADOSMODEL_H
