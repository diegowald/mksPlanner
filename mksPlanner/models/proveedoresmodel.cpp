#include "proveedoresmodel.h"

#include <QSharedPointer>
#include "models/proveedor.h"
#include "views/dlgeditproveedor.h"


ProveedoresModel::ProveedoresModel(QObject *parent)
    : ModelBase(Tables::Proveedores, "proveedores", false, "library", parent)
{
    defineColumnNames();
}

void ProveedoresModel::defineColumnNames()
{
    setField(1, "Nombre");
    setField(2, "Contacto");
    setField(3, "eMail");
    setField(4, "Telefono");
    setField(5, "Dirección");
}

/*QVariant ProveedoresModel::headerData(int section, Qt::Orientation orientation, int role) const
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
                return QString("Nombre");
                break;
            }
            case 2:
            {
                return QString("Contacto");
                break;
            }
            case 3:
            {
                return QString("eMail");
                break;
            }
            case 4:
            {
                return QString("Telefono");
                break;
            }
            case 5:
            {
                return QString("Dirección");
                break;
            }
            default:
                break;
            }
        }
        return section;
    }
    return QAbstractItemModel::headerData(section, orientation, role);
}*/

QVariant ProveedoresModel::modelData(EntityBasePtr entity, int column, int role) const
{
    QVariant result = QVariant();
    ProveedorPtr prov = qSharedPointerDynamicCast<Proveedor>(entity);
    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        switch (column)
        {
        case 0:
            result = prov->id();
            break;
        case 1:
            result = prov->name();
            break;
        case 2:
            result = prov->contacto();
            break;
        case 3:
            result = prov->email();
            break;
        case 4:
            result = prov->telefono();
            break;
        case 5:
            result = prov->direccion();
            break;
        default:
            result = QVariant();
            break;
        }
    }
    return result;
}

bool ProveedoresModel::modelSetData(EntityBasePtr entity, int column, const QVariant &value, int role)
{
    ProveedorPtr p = qSharedPointerDynamicCast<Proveedor>(entity);
    bool result = false;
    switch (column)
    {
    case 0:
        result = true;
        break;
    case 1:
        p->setName(value.toString());
        result = true;
        break;
    case 2:
        p->setContacto(value.toString());
        result = true;
        break;
    case 3:
        p->setEMail(value.toString());
        result = true;
        break;
    case 4:
        p->setTelefono(value.toString());
        result = true;
        break;
    case 5:
        p->setDireccion(value.toString());
        result = true;
        break;
    default:
        break;
    }
    return result;
}

QString ProveedoresModel::_getSQLRead() const
{
    return "select * from proveedores;";
}

int ProveedoresModel::_loadEntity(QSqlRecord record)
{
    int id = record.value(record.indexOf("id")).toInt();
    QString nombre = record.value(record.indexOf("name")).toString();
    QString contacto = record.value(record.indexOf("contacto")).toString();
    QString email = record.value(record.indexOf("email")).toString();
    QString telefono = record.value(record.indexOf("telefono")).toString();
    QString direccion = record.value(record.indexOf("direccion")).toString();

    EntityBasePtr entity = ProveedorPtr::create(id, nombre, contacto,
                                                email, telefono, direccion);

    addEntity(entity);
    return id;
}

EntityBasePtr ProveedoresModel::internalCreateEntity(int assignedId)
{
    return ProveedorPtr::create(assignedId);
}


void ProveedoresModel::editEntity(int row)
{
    dlgEditProveedor dlg(this, row);
    dlg.exec();
}
