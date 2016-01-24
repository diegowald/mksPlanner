#include "costomaterialcompuesto.h"
#include <QVariant>
#include "globalcontainer.h"
#include "models/material.h"
#include "globalcontainer.h"
#include "models/componentesmateriales.h"
#include "models/costomaterialesmodel.h"
#include "models/componentematerial.h"
#include <QSharedPointer>

CostoMaterialCompuesto::CostoMaterialCompuesto(int id, int idMaterial) : EntityBase(id, false)
{
    _idMaterial = idMaterial;
}

CostoMaterialCompuesto::CostoMaterialCompuesto(int id): EntityBase(id, false)
{
    _idMaterial = -1;
}

bool CostoMaterialCompuesto::internalSetData(const int column, const QVariant &value, int role)
{
    if (role == Qt::EditRole)
    {
        switch (column)
        {
        case 1:
        {
            _idMaterial = value.toInt();
            break;
        }
        default:
            break;
        }

        return true;
    }
    return false;
}

void CostoMaterialCompuesto::setIdMaterial(int id)
{
    _idMaterial = id;
//    updateStatus(EntityStatus::modified); // Estos elementos no se guardaran en la base
}


QVariant CostoMaterialCompuesto::internalData(const int column, int role) const
{
    QVariant result;
    if (role == Qt::DisplayRole)
    {
        switch (column)
        {
        case 0:
        {
            result = id();
            break;
        }
        case 1:
        {
            result = _idMaterial;
            break;
        }
        case 2:
        {
            result = costo();
            break;
        }
        case 3:
        {
            result = desde();
            break;
        }
        default:
            break;
        }
    }
    return result;
}

QSqlQuery* CostoMaterialCompuesto::getQuery(QSqlDatabase &database)
{
    return NULL; // Este es un material compuesto, por lo que el costo siempre se calcula en base a los materiales
}

double CostoMaterialCompuesto::costo() const
{
    ComponentesMaterialesModel* modelComponentes = dynamic_cast<ComponentesMaterialesModel*>(GlobalContainer::instance().materialLibrary()->model(Tables::ComponentesMateriales));
    QList<int> idComponentes = modelComponentes->idComponentes(_idMaterial);

    CostoMaterialesModel* modelCostos = dynamic_cast<CostoMaterialesModel*>(GlobalContainer::instance().materialLibrary()->model(Tables::CostosUnitarios));

    double costoAcumulado = 0.;
    foreach (int id, idComponentes)
    {
        ComponenteMaterialPtr componente = qSharedPointerDynamicCast<ComponenteMaterial>(modelComponentes->getItem(id));
        double factor = componente->cantidad();
        CostoMaterialPtr cm = qSharedPointerDynamicCast<CostoMaterial>(modelCostos->getItemByIdMaterial(componente->idMaterial()));
        if (cm.isNull())
        {
            costoAcumulado = NAN;
            break;
        }
        double costo = cm->costo();
        costoAcumulado += factor * costo;
    }
    return costoAcumulado;
}

QDate CostoMaterialCompuesto::desde() const
{
    ComponentesMaterialesModel* modelComponentes = dynamic_cast<ComponentesMaterialesModel*>(GlobalContainer::instance().materialLibrary()->model(Tables::ComponentesMateriales));
    QList<int> idComponentes = modelComponentes->idComponentes(_idMaterial);

    CostoMaterialesModel* modelCostos = dynamic_cast<CostoMaterialesModel*>(GlobalContainer::instance().materialLibrary()->model(Tables::CostosUnitarios));

    QDate fechaCostoMasViejo = QDate::currentDate();
    foreach (int id, idComponentes)
    {
        ComponenteMaterialPtr componente = qSharedPointerDynamicCast<ComponenteMaterial>(modelComponentes->getItem(id));
        CostoMaterialPtr cm = qSharedPointerDynamicCast<CostoMaterial>(modelCostos->getItemByIdMaterial(componente->idMaterial()));
        if (cm.isNull())
        {
            fechaCostoMasViejo.setDate(0, 0, 0);
            break;
        }
        QDate fechaCosto = cm->desde();
        fechaCostoMasViejo = (fechaCosto < fechaCostoMasViejo) ? fechaCosto : fechaCostoMasViejo;
    }
    return fechaCostoMasViejo;
}


QString CostoMaterialCompuesto::toDebugString()
{
    return QString("id: %1, idMaterial: %2, costo: %3, desde: %4").arg(id())
            .arg(_idMaterial).arg(costo()).arg(desde().toString());
}
