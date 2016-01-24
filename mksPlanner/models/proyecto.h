#ifndef PROYECTO_H
#define PROYECTO_H

#include <QObject>
#include "models/entitybase.h"

class Proyecto : public EntityBase
{
    Q_OBJECT
public:
    explicit Proyecto(int id, const QString &propietario, const QString &direccion, const QString &email, const QString &telefono);
    explicit Proyecto(int id);

    virtual bool internalSetData(const int column, const QVariant &value, int role);
    virtual QSqlQuery* getQuery(QSqlDatabase &database);

    virtual QString toDebugString();

    QString propietario();
    QString direccion();
    QString email();
    QString telefono();

signals:

public slots:

private:
    QString _propietario;
    QString _direccion;
    QString _email;
    QString _telefono;
};


typedef QSharedPointer<Proyecto> ProyectoPtr;

#endif // PROYECTO_H
