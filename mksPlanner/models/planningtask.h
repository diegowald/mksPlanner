#ifndef PLANNINGTASK_H
#define PLANNINGTASK_H

#include <QObject>
#include "models/entitybase.h"
#include <QDate>
#include <KDGantt>

class PlanningTask;
typedef QSharedPointer<PlanningTask> PlanningTaskPtr;

class PlanningTask : public EntityBase
{
    Q_OBJECT
public:
    explicit PlanningTask(int id);

    explicit PlanningTask(int id, int idTareaPadre, const QString &name,
                          int idMaterialTask, int idProveedor,
                          double cantidad, const QDateTime &fechaEstimadaInicio,
                          const QDateTime &fechaEstimadaFin, KDGantt::ItemType taskType);

    int idTareaPadre() const;
    EntityBasePtr tareaPadre() const;
    QString name() const;
    int idMaterialTask() const;
    EntityBasePtr materialTask() const;
    int idProveedor() const;
    EntityBasePtr proveedor() const;
    double cantidad() const;
    QDateTime fechaEstimadaInicio() const;
    QDateTime fechaEstimadaFin() const;
    int duracion() const;
    double costo() const;
    double precio() const;
    QString tooltip() const;
    KDGantt::ItemType taskType() const;

    void setIdTareaPadre(int value);
    void setName(const QString &value);
    void setIdMaterialTask(int value);
    void setIdProveedor(int value);
    void setCantidad(double value);
    void setFechaEstimadaInicio(QDateTime &value);
    void setFechaEstimadaFin(QDateTime &value);
    void setTaskType(KDGantt::ItemType value);

    void setIdProyecto(int idProyecto);

    QMap<QString, double> listadoMateriales() const;

    QList<PlanningTaskPtr> child() const;
    void addSubTask(PlanningTaskPtr task);


private:
    QString tablaListadoMateriales() const;
private:
    int _idTareaPadre;
    QString _name;
    int _idMaterialTask;
    int _idProveedor;
    double _cantidad;
    QDateTime _fechaEstimadaInicio;
    QDateTime _fechaEstimadaFin;
    KDGantt::ItemType _taskType;

    int _idProyecto;

    //PlanningTask *_parent;
    QList<PlanningTaskPtr> _child;


    // EntityBase interface
public:
    virtual QSqlQuery *getQuery(QSqlDatabase &database);
    virtual QString toDebugString();

};

#endif // PLANNINGTASK_H
