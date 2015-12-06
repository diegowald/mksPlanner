#ifndef ENTITYBASE_H
#define ENTITYBASE_H

#include <QObject>
#include <QSharedPointer>

class EntityBase : public QObject
{
    Q_OBJECT
public:
    explicit EntityBase(QObject *parent = 0);
    explicit EntityBase(int id, QObject *parent = 0);

    bool setData(const int column, const QVariant &value, int role);
    QVariant data(const int column, int role = Qt::DisplayRole) const;

    virtual bool internalSetData(const int column, const QVariant &value, int role) = 0;
    virtual QVariant internalData(const int column, int role = Qt::DisplayRole) const = 0;

    bool isDirty() const;

    int id() const;

signals:

public slots:

private:
    bool _dirty;
    int _id;
};

typedef QSharedPointer<EntityBase> EntityBasePtr;

#endif // ENTITYBASE_H
