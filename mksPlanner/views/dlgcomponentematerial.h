#ifndef DLGCOMPONENTEMATERIAL_H
#define DLGCOMPONENTEMATERIAL_H

#include <QDialog>
#include "models/componentesmateriales.h"
#include <QMap>
#include <QVariant>
#include "models/validmaterialfiltermodel.h"


namespace Ui {
class dlgComponenteMaterial;
}

class dlgComponenteMaterial : public QDialog
{
    Q_OBJECT

public:
    explicit dlgComponenteMaterial(int idMaterialPadre, ComponentesMaterialesModel *model, int row, QWidget* parent = 0);
    ~dlgComponenteMaterial();

private slots:
    void on_buttonBox_accepted();

    void on_cboMaterial_currentIndexChanged(int index);

private:
    Ui::dlgComponenteMaterial *ui;
    ComponentesMaterialesModel *_model;
    ValidMaterialFilterModel *_materialsModel;
    EntityBasePtr _entity;
};

#endif // DLGCOMPONENTEMATERIAL_H
