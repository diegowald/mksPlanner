#ifndef ENTITYBASE_H
#define ENTITYBASE_H

#include <QObject>
#include <QSharedPointer>
#include <QSqlQuery>


enum class EntityStatus
{
    unchanged,
    added,
    modified,
    deleted
};

class EntityBase : public QObject
{
    Q_OBJECT
public:
    explicit EntityBase();
    explicit EntityBase(int id, bool isNew = false);

    //bool setData(const int column, const QVariant &value, int role);

    //virtual bool internalSetData(const int column, const QVariant &value, int role) = 0;
    virtual QSqlQuery* getQuery(QSqlDatabase &database) = 0;
    virtual QString toDebugString() = 0;

    virtual bool isDirty() const;

    int id() const;

    virtual void deleteEntity();


    EntityStatus status();

    void updateStatus(EntityStatus newStatus = EntityStatus::modified);

private:
    int _id;
    EntityStatus _status;
};

typedef QSharedPointer<EntityBase> EntityBasePtr;

#endif // ENTITYBASE_H
