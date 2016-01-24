#ifndef UNIT_H
#define UNIT_H

#include <QObject>
#include "models/entitybase.h"

class Unit : public EntityBase
{
    Q_OBJECT
public:

    explicit Unit(int id, const QString &name, const QString &description);
    explicit Unit(int id);

    virtual bool internalSetData(const int column, const QVariant &value, int role);
    virtual QString toDebugString();

    virtual QSqlQuery* getQuery(QSqlDatabase &database);

    QString name() const;
    QString description() const;
signals:

public slots:

private:
    QString _name;
    QString _description;
};

typedef QSharedPointer<Unit> UnitPtr;

#endif // UNIT_H
