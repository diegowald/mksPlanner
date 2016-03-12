#ifndef CANTIDAD_H
#define CANTIDAD_H

#include <QObject>
#include "models/unit.h"

class Cantidad : public QObject
{
    Q_OBJECT
public:
    explicit Cantidad(double value, UnitPtr unit);
    explicit Cantidad(double value);

    QString toString() const;

    double value() const;
    void setValue(double value);
signals:

public slots:
private:
    double _value;
    UnitPtr _unit;
};

typedef QSharedPointer<Cantidad> CantidadPtr;

#endif // CANTIDAD_H
