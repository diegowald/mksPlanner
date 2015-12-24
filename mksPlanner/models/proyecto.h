#ifndef PROYECTO_H
#define PROYECTO_H

#include <QObject>
#include "models/entitybase.h"

class Proyecto : public EntityBase
{
    Q_OBJECT
public:
    explicit Proyecto(int id, const QString &propietario, const QString &direccion, const QString &email, const QString &telefono, QObject *parent = 0);
    explicit Proyecto(int id, QObject *parent = 0);

    virtual bool internalSetData(const int column, const QVariant &value, int role);
    virtual QVariant internalData(const int column, int role = Qt::DisplayRole) const;
    virtual QSqlQuery* getQuery(QSqlDatabase &database);

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
