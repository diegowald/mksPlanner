#ifndef PLANNINGTASKMODEL_H
#define PLANNINGTASKMODEL_H

#include <QObject>
#include "models/modelbase.h"
#include "models/planningtask.h"



class PlanningTaskModel : public ModelBase
{
    Q_OBJECT

public:
    class Node
    {
    public:
        Node(EntityBasePtr entity, Node *parent = 0);
        virtual ~Node();

        bool createChild(EntityBasePtr entity);

        void insertChild( int i, Node* node);
        void removeChild( Node* node);
        void addChild(Node* node);

        Node* parent() const;
        void setParent(Node *parent);
        int childCount() const;
        int childNumber(Node* n) const;
        Node* child(int i) const;

        EntityBasePtr entity() const;


    private:
        Node* _parent;
        QList<Node*> _children;

        EntityBasePtr _entity;
        int _id;
    };

public:
    explicit PlanningTaskModel(int idProyecto, QObject *parent = 0);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    virtual void editEntity(int row);
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;

    virtual EntityBasePtr createEntity();
    QList<EntityBasePtr> tasks() const;
    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    Node* root() { return _root; }
    /*reimp*/ bool insertRows(int row, int count, const QModelIndex& parent = QModelIndex());
    virtual void editEntity(EntityBasePtr entity);

    int idProyecto() const;

protected:
    virtual QString _getSQLRead() const;
    virtual int _loadEntity(QSqlRecord record);
    virtual EntityBasePtr internalCreateEntity(int assignedId);
    virtual QVariant modelData(EntityBasePtr entity, int column, int role) const;
    virtual bool modelSetData(EntityBasePtr entity, int column, const QVariant &value, int role);
    virtual void defineColumnNames();

    virtual void postProcessData();

private:
    PlanningTaskPtr cast(EntityBasePtr entity);

private:
    int _idProyecto;
    Node* _root;
};

#endif // PLANNINGTASKMODEL_H
