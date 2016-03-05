#ifndef EXECUTIONTASK_H
#define EXECUTIONTASK_H

#include "models/entitybase.h"
#include <QDate>
#include <KDGantt>

class ExecutionTask;

typedef QSharedPointer<ExecutionTask> ExecutionTaskPtr;

class ExecutionTask : public EntityBase
{
    Q_OBJECT
public:
    explicit ExecutionTask(int id);

    explicit ExecutionTask(int id, int idTareaPadre, const QString &name,
                          int idMaterialTask, int idProveedor,
                          double cantidad, const QDateTime &fechaEstimadaInicio,
                          const QDateTime &fechaEstimadaFin, KDGantt::ItemType taskType,
                           int idTareaPlanificada, double pctCompletado,
                           const QDateTime &fechaRealInicio, const QDateTime &fechaRealFin);

    int idPlanningTask() const;
    EntityBasePtr planningTask() const;
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
    double pctCompletado() const;

    void setIdPlanningTask(int value);
    void setPlanningTask(EntityBasePtr entity, bool copyData);
    void setIdTareaPadre(int value);
    void setName(const QString &value);
    void setIdMaterialTask(int value);
    void setIdProveedor(int value);
    void setCantidad(double value);
    void setFechaEstimadaInicio(QDateTime &value);
    void setFechaEstimadaFin(QDateTime &value);
    void setTaskType(KDGantt::ItemType value);
    void setPctCompletado(double value);


    void setIdProyecto(int idProyecto);

    QMap<QString, double> listadoMateriales() const;

    QList<ExecutionTaskPtr> child() const;
    void addSubTask(ExecutionTaskPtr task);

public:
    virtual QString toDebugString();
    virtual QSqlQuery *getQuery(QSqlDatabase &database);

private:
    QString tablaListadoMateriales() const;


signals:

public slots:

private:
    int _idPlanningTask;
    int _idTareaPadre;
    QString _name;
    int _idMaterialTask;
    int _idProveedor;
    double _cantidad;
    QDateTime _fechaEstimadaInicio;
    QDateTime _fechaEstimadaFin;
    QDateTime _fechaRealInicio;
    QDateTime _fechaRealFin;
    double _pctCompletado;
    KDGantt::ItemType _taskType;

    int _idProyecto;

    //PlanningTask *_parent;
    QList<ExecutionTaskPtr> _child;
};

#endif // EXECUTIONTASK_H
