#include "costomaterialcompuesto.h"
#include <QVariant>
#include "globalcontainer.h"
#include "models/material.h"
#include "globalcontainer.h"
#include "models/componentesmateriales.h"
#include "models/costomaterialesmodel.h"
#include "models/componentematerial.h"
#include <QSharedPointer>

CostoMaterialCompuesto::CostoMaterialCompuesto(int id, int idMaterial) : CostoMaterial(id, idMaterial, 0., QDate(0, 0, 0))
{
    _idMaterial = idMaterial;
}

CostoMaterialCompuesto::CostoMaterialCompuesto(int id): CostoMaterial(id)
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

QSqlQuery* CostoMaterialCompuesto::getQuery(QSqlDatabase &/*database*/)
{
    return NULL; // Este es un material compuesto, por lo que el costo siempre se calcula en base a los materiales
}

double CostoMaterialCompuesto::costo() const
{
    ComponentesMaterialesModel* modelComponentes = dynamic_cast<ComponentesMaterialesModel*>(GlobalContainer::instance().library()->model(Tables::ComponentesMateriales));
    QList<int> idComponentes = modelComponentes->idComponentes(_idMaterial);

    CostoMaterialesModel* modelCostos = dynamic_cast<CostoMaterialesModel*>(GlobalContainer::instance().library()->model(Tables::CostosUnitarios));

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
    ComponentesMaterialesModel* modelComponentes = dynamic_cast<ComponentesMaterialesModel*>(GlobalContainer::instance().library()->model(Tables::ComponentesMateriales));
    QList<int> idComponentes = modelComponentes->idComponentes(_idMaterial);

    CostoMaterialesModel* modelCostos = dynamic_cast<CostoMaterialesModel*>(GlobalContainer::instance().library()->model(Tables::CostosUnitarios));

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
