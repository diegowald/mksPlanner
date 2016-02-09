#ifndef PROYECTO_H
#define PROYECTO_H

#include <QObject>
#include "models/entitybase.h"
#include <QDate>


class Proyecto : public EntityBase
{
    Q_OBJECT
public:
    explicit Proyecto(int id, const QString &propietario,
                      const QString &direccion, const QString &email,
                      const QString &telefono,
                      QDate &fechaEstimadaInicio,
                      QDate &fechaEstimadaFinalizacion);

    explicit Proyecto(int id);

    void setIdProyectoInterno(int value);

    //virtual bool internalSetData(const int column, const QVariant &value, int role);
    virtual QSqlQuery* getQuery(QSqlDatabase &database);

    virtual QString toDebugString();

    QString propietario() const;
    QString direccion() const;
    QString email() const;
    QString telefono() const;
    QDate fechaEstimadaInicio() const;
    QDate fechaEstimadaFinalizacion() const;
    int plazoEstimado() const;
    double costoEstimado() const;

    void setPropietario(const QString& value);
    void setDireccion(const QString& value);
    void setEMail(const QString& value);
    void setTelefono(const QString& value);
    void setFechaEstimadaInicio(QDate &value);
    void setFechaEstimadaFinalizacion(QDate &value);

signals:

public slots:

private:
    QString _propietario;
    QString _direccion;
    QString _email;
    QString _telefono;
    QDate _fechaEstimadaInicio;
    QDate _fechaEstimadaFinalizacion;

    int _idProyectoInterno;
};


typedef QSharedPointer<Proyecto> ProyectoPtr;

#endif // PROYECTO_H
