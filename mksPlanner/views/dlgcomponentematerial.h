#ifndef DLGCOMPONENTEMATERIAL_H
#define DLGCOMPONENTEMATERIAL_H

#include <QDialog>
#include "models/componentesmateriales.h"
#include <QMap>
#include <QVariant>

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
    EntityBasePtr _entity;
};

#endif // DLGCOMPONENTEMATERIAL_H
