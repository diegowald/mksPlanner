#ifndef MATERIAL_H
#define MATERIAL_H

#include <QObject>
#include "models/entitybase.h"

class Material : public EntityBase
{
    Q_OBJECT
public:
    explicit Material(int id, const QString &name, const QString &description, int idUnit);

    virtual bool internalSetData(const int column, const QVariant &value, int role);
    virtual QVariant internalData(const int column, int role = Qt::DisplayRole) const;

    virtual QSqlQuery* getQuery(QSqlDatabase &database);

signals:

public slots:

private:
    QString _name;
    QString _description;
    int _idUnit;
};

typedef QSharedPointer<Material> MaterialPtr;

#endif // MATERIAL_H
