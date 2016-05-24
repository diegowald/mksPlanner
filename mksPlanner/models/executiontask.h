#ifndef EXECUTIONTASK_H
#define EXECUTIONTASK_H

#include "models/entitybase.h"
#include <QDate>
#include <KDGantt>
#include "models/cantidad.h"



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
                           int idTareaPlanificada,
                           const QDateTime &fechaRealInicio, const QDateTime &fechaRealFin, bool isSplittedPart,
                           int idCertificacion, double cantidadRealizada);

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
    double cantidadRealizada() const;
    double cantidadCertificada() const;
    QDateTime fechaEstimadaInicio() const;
    QDateTime fechaEstimadaFin() const;
    QDateTime fechaRealInicio() const;
    QDateTime fechaRealFin() const;
    int duracion() const;
    double costo() const;
    double precio() const;
    QString tooltip() const;
    KDGantt::ItemType taskType() const;
    double pctCompletado() const;
    double pctCompletadoInSubTask() const;
    double rendimientoReal() const;
    bool canStart() const;
    int idCertificacion() const;
    void copyDataFrom(ExecutionTaskPtr from);

    void setIdPlanningTask(int value);
    void setPlanningTask(EntityBasePtr entity, bool copyData);
    void setIdTareaPadre(int value);
    void setName(const QString &value);
    void setIdMaterialTask(int value);
    void setIdProveedor(int value);
    void setCantidad(double value);
    void setCantidadRealizadaEnSubTarea(double value);
    void setFechaEstimadaInicio(const QDateTime &value);
    void setFechaEstimadaFin(const QDateTime &value);
    void setFechaRealInicio(const QDateTime &value);
    void setFechaRealFin(const QDateTime &value);
    void setTaskType(KDGantt::ItemType value);
    void setPctCompletado(double value);
    void markAsCompleted();

    void setIdCertificacion(int idCertificacion);

    void setIdProyecto(int idProyecto);

    QMap<QString, CantidadPtr> listadoMateriales() const;

    QList<ExecutionTaskPtr> child() const;

    bool canBeSplitted() const;
    bool isPctEditable() const;

    bool isSplittedPart() const;
    void setIsSplittedPart(bool value);
    bool hasChild() const;

    QString cantidadToString() const;
    QString cantidadRealizadaToString() const;

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
    double _cantidadRealizada;
    QDateTime _fechaEstimadaInicio;
    QDateTime _fechaEstimadaFin;
    QDateTime _fechaRealInicio;
    QDateTime _fechaRealFin;
    KDGantt::ItemType _taskType;
    bool _isSplittedPart;
    int _idCertificacion;

    int _idProyecto;
    //PlanningTask *_parent;
};

#endif // EXECUTIONTASK_H
