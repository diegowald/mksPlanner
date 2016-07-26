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
    setField(1, "Nombre",
             [&] (EntityBasePtr entity, int role) -> QVariant
    {
        QVariant v;
        switch(role)
        {
        case Qt::DisplayRole:
        case Qt::EditRole:
            v = cast(entity)->name();
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
            cast(entity)->setName(value.toString());
            return true;
        }
        else
        {
            return false;
        }
    });

    setField(2, "Contacto",
             [&] (EntityBasePtr entity, int role) -> QVariant
    {
        QVariant v;
        switch (role)
        {
        case Qt::DisplayRole:
        case Qt::EditRole:
            v = cast(entity)->contacto();
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
            cast(entity)->setContacto(value.toString());
            return true;
        }
        else
        {
            return false;
        }
    });

    setField(3, "eMail",
             [&] (EntityBasePtr entity, int role) -> QVariant
    {
        QVariant v;
        switch (role)
        {
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
    {
        QVariant v;
        switch (role)
        {
        case Qt::DisplayRole:
        case Qt::EditRole:
            v = cast(entity)->telefono();
            break;
        default:
            v = QVariant();
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

    setField(5, "Dirección",
             [&] (EntityBasePtr entity, int role) -> QVariant
    {
        QVariant v;
        switch (role)
        {
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
    [&] (EntityBasePtr entity, const QVariant& value, int role) -> bool
    {
        if (role == Qt::EditRole)
        {
            cast(entity)->setDireccion(value.toString());
            return true;
        }
        else
        {
            return false;
        }
    });

}

/*QVariant ProveedoresModel::modelData(EntityBasePtr entity, int column, int role) const
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
}*/

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
    QString web = record.value(record.indexOf("web")).toString();

    EntityBasePtr entity = ProveedorPtr::create(id, nombre, contacto,
                                                email, telefono, direccion, web);

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

ProveedorPtr ProveedoresModel::cast(EntityBasePtr entity)
{
    return qSharedPointerDynamicCast<Proveedor>(entity);
}
