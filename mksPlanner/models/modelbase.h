#ifndef MODELBASE_H
#define MODELBASE_H

#include <QObject>
#include "persistance/persister.h"
#include <QAbstractTableModel>
#include <QSharedPointer>

class ModelBase : public QAbstractTableModel, virtual public PersisterBase
{
    Q_OBJECT
public:
    explicit ModelBase(QObject *parent = 0);

signals:

public slots:
};

typedef QSharedPointer<ModelBase> ModelBasePtr;

#endif // MODELBASE_H
