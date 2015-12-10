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
    explicit EntityBase(int id);

    bool setData(const int column, const QVariant &value, int role);
    QVariant data(const int column, int role = Qt::DisplayRole) const;

    virtual bool internalSetData(const int column, const QVariant &value, int role) = 0;
    virtual QVariant internalData(const int column, int role = Qt::DisplayRole) const = 0;

    bool isDirty() const;

    int id() const;

    virtual void deleteEntity();

    virtual QSqlQuery* getQuery(QSqlDatabase &database) = 0;

    EntityStatus status();

    void updateStatus(EntityStatus newStatus);


signals:

public slots:

private:
    bool _dirty;
    int _id;
    EntityStatus _status;
};

typedef QSharedPointer<EntityBase> EntityBasePtr;

#endif // ENTITYBASE_H