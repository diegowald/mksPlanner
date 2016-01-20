#ifndef RUBRO_H
#define RUBRO_H

#include <QObject>
#include "models/entitybase.h"

class Rubro : public EntityBase
{
    Q_OBJECT
public:
    explicit Rubro(int id);
    explicit Rubro(int id, const QString &name, const QString &description, bool isTask);

    virtual bool internalSetData(const int column, const QVariant &value, int role);
    virtual QVariant internalData(const int column, int role = Qt::DisplayRole) const;
    virtual QString toDebugString();

    virtual QSqlQuery* getQuery(QSqlDatabase &database);

    QString name() const;
    QString description() const;

signals:

public slots:

private:
    QString _name;
    QString _description;
    bool _isTask;
};

typedef QSharedPointer<Rubro> RubroPtr;

#endif // RUBRO_H
