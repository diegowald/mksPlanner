#ifndef PROYECTOMODEL_H
#define PROYECTOMODEL_H

#include <QObject>
#include "models/modelbase.h"

class ProyectoModel : public ModelBase
{
    Q_OBJECT
public:
    explicit ProyectoModel(QObject *parent = 0);

signals:

public slots:
};

#endif // PROYECTOMODEL_H
