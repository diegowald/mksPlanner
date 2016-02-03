#include "proyectomodel.h"
#include "views/dlgeditproject.h"
#include "models/proyecto.h"


ProyectoModel::ProyectoModel(int idProyecto, QObject *parent) : ModelBase("prouecto", false, "proyecto", parent)
{
    defineColumnNames();
    _idProyecto = idProyecto;
}

int ProyectoModel::columnCount(const QModelIndex &/*parent*/) const
{
    return 7;
}

void ProyectoModel::defineColumnNames()
{
    setField(0, "id");
    setField(1, "Propietario");
    setField(2, "Direccion");
    setField(3, "Email");
    setField(4, "Telefono");
    setField(5, "Fecha estimada de Inicio");
    setField(6, "Fecha estimada de finalización");
}

QVariant ProyectoModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal)
        {
            switch (section)
            {
            case 0:
            {
                return QString("id");
                break;
            }
            case 1:
            {
                return QString("Propietario");
                break;
            }
            case 2:
            {
                return QString("Direccion");
                break;
            }
            case 3:
            {
                return QString("Email");
                break;
            }
            case 4:
            {
                return QString("Telefono");
                break;
            }
            case 5:
            {
                return QString("Fecha estimada de Inicio");
                break;
            }
            case 6:
            {
                return QString("Fecha estimada de finalización");
                break;
            }
            default:
                break;
            }
        }
        return section;
    }
    return QAbstractItemModel::headerData(section, orientation, role);
}

QVariant ProyectoModel::modelData(EntityBasePtr entity, int column, int role) const
{
    ProyectoPtr p = qSharedPointerDynamicCast<Proyecto>(entity);
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
    default:
        return QVariant();
        break;
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
    default:
        break;
    }
    return result;
}


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

    EntityBasePtr entity = ProyectoPtr::create(id, propietario, direccion, email, telefono, fechaEstimadaInicio, fechaEstimadaFin);
    addEntity(entity);
    return id;
}

EntityBasePtr ProyectoModel::internalCreateEntity(int assignedId)
{
    return ProyectoPtr::create(assignedId);
}


void ProyectoModel::editEntity(int row)
{
    dlgEditProject dlg(this, row);
    dlg.exec();
}
