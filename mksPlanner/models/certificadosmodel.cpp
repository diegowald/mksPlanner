#include "certificadosmodel.h"
#include <QSharedPointer>
//#include "views/dlgEditCertificacion.h"
#include <QSet>

#include <QDebug>

CertificadosModel::CertificadosModel(int idProyecto, QObject *parent) :
    ModelBase(Tables::Certificados, "certificados", false, "proyecto", parent)
{
    _idProyecto = idProyecto;
    defineColumnNames();
}

void CertificadosModel::defineColumnNames()
{
    setField(1, "Nro. Certificado",
             [&] (EntityBasePtr e, int role) -> QVariant
    {
        QVariant v;
        switch (role)
        {
        case Qt::DisplayRole:
        case Qt::EditRole:
            v = cast(e)->nroCertificado();
        default:
            v = QVariant();
        }
        return v;
    });
}


QString CertificadosModel::_getSQLRead() const
{
    return "select * from certificados;";
}

int CertificadosModel::_loadEntity(QSqlRecord record)
{
    int id = record.value(record.indexOf("id")).toInt();
    int idCertificacion = record.value(record.indexOf("idCertificacion")).toInt();
    int idProveedor = record.value(record.indexOf("idProveedor")).toInt();
    bool isClient = record.value(record.indexOf("isClient")).toBool();
    Certificado::StatusCertificado statusCertificado =
            static_cast<Certificado::StatusCertificado>(
                record.value(record.indexOf("statusCertificado")).toInt());
    QDate fechaEmision = record.value(record.indexOf("fechaEmision")).toDate();
    QDate desde = record.value(record.indexOf("desde")).toDate();
    QDate hasta = record.value(record.indexOf("hasta")).toDate();

    EntityBasePtr entity = CertificadoPtr::create(id, idCertificacion, idProveedor,
                                                  isClient, statusCertificado,
                                                  fechaEmision, desde, hasta);
    cast(entity)->setIdProyecto(_idProyecto);
    addEntity(entity);
    return id;
}

EntityBasePtr CertificadosModel::internalCreateEntity(int assignedId)
{
    EntityBasePtr entity = CertificadoPtr::create(assignedId);
    cast(entity)->setIdProyecto(_idProyecto);
    return entity;
}


void CertificadosModel::editEntity(int row)
{
/*    dlgEditCertificacion dlg(this, row);
    dlg.exec();*/
}

CertificadoPtr CertificadosModel::cast(EntityBasePtr entity)
{
    return qSharedPointerDynamicCast<Certificado>(entity);
}
