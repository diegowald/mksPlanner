#ifndef FIELDBEHAVIOUR_H
#define FIELDBEHAVIOUR_H

#include <QObject>
#include <QVariant>
#include "models/entitybase.h"
#include <functional>
#include <QSharedPointer>

typedef std::function<QVariant (EntityBasePtr, int)> GetterFunctor;
typedef std::function<bool (EntityBasePtr, const QVariant&, int)> SetterFunctor;

class FieldBehaviour : public QObject
{
    Q_OBJECT
public:
    explicit FieldBehaviour(const QString &name,
                            GetterFunctor getter,
                            SetterFunctor setter);

    explicit FieldBehaviour(const QString &name,
                            GetterFunctor getter);

    QVariant get(EntityBasePtr entity, int role);
    bool set(EntityBasePtr entity, const QVariant &value, int role);
    QString name() const;
signals:

public slots:
private:
    GetterFunctor _getter;
    SetterFunctor _setter;
    QString _name;
};

typedef QSharedPointer<FieldBehaviour> FieldBehaviourPtr;

#endif // FIELDBEHAVIOUR_H
