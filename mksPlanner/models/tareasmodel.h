#ifndef TAREASMODEL_H
#define TAREASMODEL_H

#include <QObject>
#include "models/materialesbasemodel.h"


class TareasModel : public MaterialesBaseModel
{
    Q_OBJECT
public:
    explicit TareasModel(QObject *parent = 0);

protected:
    virtual EntityBasePtr internalCreateEntity(int assignedId);

signals:

public slots:
};

#endif // TAREASMODEL_H

