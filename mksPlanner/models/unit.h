#ifndef UNIT_H
#define UNIT_H

#include <QObject>
#include "models/entitybase.h"

class Unit : public EntityBase
{
    Q_OBJECT
public:

    explicit Unit(int id, const QString &name, const QString &description, QObject *parent = 0);

    virtual bool internalSetData(const int column, const QVariant &value, int role);
    virtual QVariant internalData(const int column, int role = Qt::DisplayRole) const;

    virtual QSqlQuery* getQuery(QSqlDatabase &database);

signals:

public slots:

private:
    int _id;
    QString _name;
    QString _description;
};

typedef QSharedPointer<Unit> UnitPtr;

#endif // UNIT_H
