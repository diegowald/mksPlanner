#include "material.h"
#include <QVariant>
#include "globalcontainer.h"
#include "models/unit.h"
#include "models/rubro.h"
#include <QSet>
#include "models/componentesmateriales.h"
#include "models/rubro.h"
#include "models/componentematerial.h"



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


QSqlQuery* Material::getQuery(QSqlDatabase &database)
{
    QSqlQuery *query = NULL;
    switch (status())
    {
    case EntityStatus::added:
    {
        query = new QSqlQuery(database);
        query->prepare("INSERT INTO materiales (id, name, description, idUnit, RubroID) VALUES (:id, :nombre, :descripcion, :idUnit, :idRubro);");
        query->bindValue(":id", id());
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

QMap<QString, CantidadPtr> Material::listadoMaterialesCantidades(double cantidadARealizar)
{
    QMap<QString, CantidadPtr> result;
    if (!isCompuesto())
    {
        result[_name] = CantidadPtr::create(cantidadARealizar, qSharedPointerDynamicCast<Unit>(GlobalContainer::instance().library()->model(Tables::Unidades)->getItem(_idUnit)));
    }
    else
    {
        ComponentesMaterialesModel* model = dynamic_cast<ComponentesMaterialesModel*>(GlobalContainer::instance().library()->model(Tables::ComponentesMateriales));
        QList<int> componentes = model->idComponentes(id());
        foreach (int idComponente, componentes)
        {
            EntityBasePtr entity = model->getItem(idComponente);
            ComponenteMaterialPtr cm = qSharedPointerDynamicCast<ComponenteMaterial>(entity);
            MaterialPtr m = qSharedPointerDynamicCast<Material>(cm->material());
            QMap<QString, CantidadPtr> partialResult = m->listadoMaterialesCantidades(cm->cantidad() * cantidadARealizar);
            foreach (QString material, partialResult.keys())
            {
                if (!result.contains(material))
                {
                    result[material] = partialResult[material];
                }
                else
                {
                    CantidadPtr c = result[material];
                    c->setValue(c->value() + partialResult[material]->value());
                }
            }
        }
    }
    return result;
}
