#ifndef MATERIALESMODEL_H
#define MATERIALESMODEL_H

#include <QObject>
#include "models/materialesbasemodel.h"

class MaterialesModel : public MaterialesBaseModel
{
    Q_OBJECT
public:
    explicit MaterialesModel(QObject *parent = 0);

protected:
    virtual EntityBasePtr internalCreateEntity(int assignedId);

signals:

public slots:
};

#endif // MATERIALESMODEL_H
