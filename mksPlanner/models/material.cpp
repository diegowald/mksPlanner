#include "material.h"
#include <QVariant>
#include "globalcontainer.h"
#include "models/unit.h"
#include "models/rubro.h"
#include <QSet>
#include "models/componentesmateriales.h"
#include "models/rubro.h"
#include <QDebug>

Material::Material(int id, const QString &name, const QString &description, int idUnit, int idRubro) : EntityBase(id)
{
    _name = name;
    _description = description;
    _idUnit = idUnit;
    _idRubro = idRubro;
}

Material::Material(int id):EntityBase(id, true)
{
    _name = "";
    _description = "";
    _idUnit = -1;
    _idRubro = -1;
}

/*bool Material::internalSetData(const int column, const QVariant &value, int role)
{
    bool result = false;
    switch (column)
    {
    case 1:
        _name = value.toString();
        result = true;
        break;
    case 2:
        _description = value.toString();
        result = true;
        break;
    case 3:
        _idUnit = value.toInt();
        result = true;
        break;
    case 4:
        _idRubro = value.toInt();
        result = true;
        break;
    default:
        break;
    }
    return result;
}*/

/*QVariant Material::internalData(const int column, int role) const
{
    QVariant result;
    switch (column)
    {
    case 0:
        result = id();
        break;
    case 1:
        result = _name;
        break;
    case 2:
        result = _description;
        break;
    case 3:
        if (!unit().isNull())
        {
            result = qSharedPointerDynamicCast<Unit>(unit())->name();
        }
        break;
    case 4:
        if (!rubro().isNull())
        {
            result = qSharedPointerDynamicCast<Rubro>(rubro())->name();
        }
        break;
    case 5:
        result = _isUsableMaterial;
        break;
    case 6:
        result = _isTask;
        break;
    default:
        break;
    }
    return result;
}*/

QSqlQuery* Material::getQuery(QSqlDatabase &database)
{
    QSqlQuery *query;
    switch (status())
    {
    case EntityStatus::added:
    {
        query = new QSqlQuery(database);
        query->prepare("INSERT INTO materiales (name, description, idUnit, RubroID) VALUES (:nombre, :descripcion, :idUnit, :idRubro);");
        query->bindValue(":nombre", _name);
        query->bindValue(":descripcion", _description);
        query->bindValue(":idUnit", _idUnit);
        query->bindValue(":idRubro", _idRubro);
        break;
    }
    case EntityStatus::deleted:
    {
        query = new QSqlQuery(database);
        query->prepare("DELETE FROM materiales WHERE id = :id;");
        query->bindValue(":id", id());
        break;
    }
    case EntityStatus::modified:
    {
        query = new QSqlQuery(database);
        query->prepare("UPDATE materiales SET name = :nombre, description = :descripcion, idUnit = :idUnit, RubroID = :idRubro WHERE id = :id;");
        query->bindValue(":nombre", _name);
        query->bindValue(":descripcion", _description);
        query->bindValue(":idUnit", _idUnit);
        query->bindValue(":idRubro", _idRubro);
        query->bindValue(":id", id());
        qDebug() << id();
        break;
    }
    case EntityStatus::unchanged:
        query = NULL;
        break;
    }
    return query;
}

QString Material::name() const
{
    return _name;
}

QString Material::description() const
{
    return _description;
}

int Material::idUnit() const
{
    return _idUnit;
}

EntityBasePtr Material::unit() const
{
    return GlobalContainer::instance().library()->model(Tables::Unidades)->getItem(_idUnit);
}

int Material::idRubro() const
{
    return _idRubro;
}

EntityBasePtr Material::rubro() const
{
    return GlobalContainer::instance().library()->model(Tables::Rubros)->getItem(_idRubro);
}

QSet<int> Material::materialsComposedBy()
{
    ComponentesMaterialesModel* model = dynamic_cast<ComponentesMaterialesModel*>(GlobalContainer::instance().library()->model(Tables::ComponentesMateriales));
    return model->compuestosPor(id());
}

void Material::setUnit(int idUnit)
{
    _idUnit = idUnit;
    updateStatus(EntityStatus::modified);
}

void Material::setRubro(int idRubro)
{
    _idRubro = idRubro;
    updateStatus(EntityStatus::modified);
}

QString Material::toDebugString()
{
    return QString("id: %1, name: %2, description: %3, idUnit: %4, idRubro: %5")
            .arg(id()).arg(_name).arg(_description).arg(_idUnit).arg(_idRubro);

}

bool Material::isTask() const
{
    if (_idRubro != -1)
    {
        RubroPtr rubro = qSharedPointerDynamicCast<Rubro>(GlobalContainer::instance().library()->model(Tables::Rubros)->getItem(_idRubro));
        return rubro.isNull() ? false : rubro->isTask();
    }
    return false;
}


bool Material::isCompuesto() const
{
    ComponentesMaterialesModel* model = dynamic_cast<ComponentesMaterialesModel*>(GlobalContainer::instance().library()->model(Tables::ComponentesMateriales));
    return model->idComponentes(id()).count() > 0;
}

void Material::setName(const QString &value)
{
    _name = value;
    updateStatus();
}

void Material::setDescription(const QString &value)
{
    _description = value;
    updateStatus();
}
