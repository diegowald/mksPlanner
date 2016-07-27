#include "proyectomodel.h"
#include "views/dlgeditproject.h"
#include "models/proyecto.h"


ProyectoModel::ProyectoModel(int idProyecto, QObject *parent) :
    ModelBase(Tables::Proyectos, "proyecto", false, "proyecto", parent)
{
    defineColumnNames();
    _idProyecto = idProyecto;
}

void ProyectoModel::defineColumnNames()
{
    setField(1, "Propietario",
             [&] (EntityBasePtr entity, int role) -> QVariant
    {
        QVariant v;
        switch (role) {
        case Qt::DisplayRole:
        case Qt::EditRole:
            v = cast(entity)->propietario();
            break;
        default:
            v = QVariant();
            break;
        }
        return v;
    },
    [&] (EntityBasePtr entitty, const QVariant& value, int role) -> bool
    {
        if (role == Qt::EditRole)
        {
            cast(entitty)->setPropietario(value.toString());
            return true;
        }
        else
        {
            return false;
        }
    });

    setField(2, "Direccion",
             [&] (EntityBasePtr entity, int role) -> QVariant
    {
        QVariant v;
        switch (role) {
        case Qt::DisplayRole:
        case Qt::EditRole:
            v = cast(entity)->direccion();
            break;
        default:
            v = QVariant();
            break;
        }
        return v;
    },
    [&] (EntityBasePtr entitty, const QVariant& value, int role) -> bool
    {
        if (role == Qt::EditRole)
        {
            cast(entitty)->setDireccion(value.toString());
            return true;
        }
        else
        {
            return false;
        }
    });

    setField(3, "Email",
             [&] (EntityBasePtr entity, int role) -> QVariant
    {
        QVariant v;
        switch (role) {
        case Qt::DisplayRole:
        case Qt::EditRole:
            v = cast(entity)->email();
            break;
        default:
            v = QVariant();
            break;
        }
        return v;
    },
    [&] (EntityBasePtr entity, const QVariant& value, int role) -> bool
    {
        if (role == Qt::EditRole)
        {
            cast(entity)->setEMail(value.toString());
            return true;
        }
        else
        {
            return false;
        }

    });

    setField(4, "Telefono",
             [&] (EntityBasePtr entity, int role) -> QVariant
    {                 QVariant v;
                      switch (role) {
                      case Qt::DisplayRole:
                      case Qt::EditRole:
                          v = cast(entity)->telefono();
                          break;
                      default:
                          v = QVariant();
                          break;
                      }
                                    return v;
    },
    [&] (EntityBasePtr entity, const QVariant& value, int role) -> bool
    {
        if (role == Qt::EditRole)
        {
            cast(entity)->setTelefono(value.toString());
            return true;
        }
        else
        {
            return false;
        }
    });

    setField(5, "Fecha estimada de Inicio",
             [&] (EntityBasePtr entity, int role) -> QVariant
    {                 QVariant v;
                      switch (role) {
                      case Qt::DisplayRole:
                      case Qt::EditRole:
                          v = cast(entity)->fechaEstimadaInicio();
                          break;
                      default:
                          v = QVariant();
                          break;
                      }
                                    return v;
    },
    [&] (EntityBasePtr entity, const QVariant& value, int role) -> bool
    {
        if (role == Qt::EditRole)
        {
            QDate dt = value.toDate();
            cast(entity)->setFechaEstimadaInicio(dt);
            return true;
        }
        else
        {
            return false;
        }
    });

    setField(6, "Fecha estimada de finalización",
             [&] (EntityBasePtr entity, int role) -> QVariant
    {                 QVariant v;
                      switch (role) {
                      case Qt::DisplayRole:
                      case Qt::EditRole:
                          v = cast(entity)->fechaEstimadaFinalizacion();
                          break;
                      default:
                          v = QVariant();
                          break;
                      }
                                    return v;
    },
    [&] (EntityBasePtr entity, const QVariant& value, int role) -> bool
    {
        if (role == Qt::EditRole)
        {
            QDate dt = value.toDate();
            cast(entity)->setFechaEstimadaFinalizacion(dt);
            return true;
        }
        else
        {
            return false;
        }

    });

    setField(7, "Plazo",
             [&] (EntityBasePtr entity, int role) -> QVariant
    {                 QVariant v;
                      switch (role) {
                      case Qt::DisplayRole:
                      case Qt::EditRole:
                          v = cast(entity)->plazoEstimado();
                          break;
                      default:
                          v = QVariant();
                          break;
                      }
                                    return v;
    });

    setField(8, "Costo",
             [&] (EntityBasePtr entity, int role) -> QVariant
    {                 QVariant v;
                      switch (role) {
                      case Qt::DisplayRole:
                      case Qt::EditRole:
                          v = cast(entity)->costoEstimado();
                          break;
                      default:
                          v = QVariant();
                          break;
                      }
                                    return v;
    });
}

/*QVariant ProyectoModel::modelData(EntityBasePtr entity, int column, int role) const
{
    ProyectoPtr p = qSharedPointerDynamicCast<Proyecto>(entity);
    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        switch (column)
        {
        case 0:
            return p->id();
            break;
        case 1:
        {
            return p->propietario();
            break;
        }
        case 2:
        {
            return p->direccion();
            break;
        }
        case 3:
        {
            return p->email();
            break;
        }
        case 4:
        {
            return p->telefono();
            break;
        }
        case 5:
        {
            return p->fechaEstimadaInicio();
            break;
        }
        case 6:
        {
            return p->fechaEstimadaFinalizacion();
            break;
        }
        case 7:
        {
            return p->plazoEstimado();
            break;
        }
        case 8:
        {
            return p->costoEstimado();
            break;
        }
        default:
            return QVariant();
            break;
        }
    }
}

bool ProyectoModel::modelSetData(EntityBasePtr entity, int column, const QVariant &value, int role)
{
    ProyectoPtr p = qSharedPointerDynamicCast<Proyecto>(entity);
    bool result = false;
    switch (column)
    {
    case 0:
        result = true;
        break;
    case 1:
        p->setPropietario(value.toString());
        result = true;
        break;
    case 2:
        p->setDireccion(value.toString());
        result = true;
        break;
    case 3:
    {
        p->setEMail(value.toString());
        result = true;
        break;
    }
    case 4:
    {
        p->setTelefono(value.toString());
        result = true;
        break;
    }
    case 5:
    {
        QDate dt = value.toDate();
        p->setFechaEstimadaInicio(dt);
        result = true;
        break;
    }
    case 6:
    {
        QDate dt = value.toDate();
        p->setFechaEstimadaFinalizacion(dt);
        result = true;
        break;
    }
    case 7:
        break;
    case 8:
        break;
    default:
        break;
    }
    return result;
}*/


QString ProyectoModel::_getSQLRead() const
{
    return "select * from proyectos limit 1;";
}

int ProyectoModel::_loadEntity(QSqlRecord record)
{
    int id = record.value(record.indexOf("id")).toInt();
    QString propietario = record.value(record.indexOf("propietario")).toString();
    QString direccion = record.value(record.indexOf("direccion")).toString();
    QString email = record.value(record.indexOf("email")).toString();
    QString telefono = record.value(record.indexOf("telefono")).toString();
    QDate fechaEstimadaInicio = record.value(record.indexOf("fechaEstimadaInicio")).toDate();
    QDate fechaEstimadaFin = record.value(record.indexOf("fechaEstimadaFinalizacion")).toDate();
    Proyecto::ProjectStatus status = static_cast<Proyecto::ProjectStatus>(record.value(record.indexOf("status")).toInt());
    Proyecto::TipoProyecto tipoProyecto = static_cast<Proyecto::TipoProyecto>(record.value(record.indexOf("idTipoDeObra")).toInt());

    EntityBasePtr entity = ProyectoPtr::create(id, propietario, direccion, email, telefono, fechaEstimadaInicio, fechaEstimadaFin, status, tipoProyecto);
    qSharedPointerDynamicCast<Proyecto>(entity)->setIdProyectoInterno(_idProyecto);
    addEntity(entity);
    return id;
}

EntityBasePtr ProyectoModel::internalCreateEntity(int assignedId)
{
    ProyectoPtr p = ProyectoPtr::create(assignedId);
    p->setIdProyectoInterno(_idProyecto);
    return p;
}


void ProyectoModel::editEntity(int row)
{
    dlgEditProject dlg(this, row);
    dlg.exec();
}

QString ProyectoModel::filename() const
{
    return PersisterBase::filename();
}

ProyectoPtr ProyectoModel::cast(EntityBasePtr entity)
{
    return qSharedPointerDynamicCast<Proyecto>(entity);
}
