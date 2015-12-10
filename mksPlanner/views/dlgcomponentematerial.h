#ifndef DLGCOMPONENTEMATERIAL_H
#define DLGCOMPONENTEMATERIAL_H

#include <QDialog>
#include "models/componentesmateriales.h"
#include <QDataWidgetMapper>

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

private:
    Ui::dlgComponenteMaterial *ui;
    ComponentesMaterialesModel *_model;
    QDataWidgetMapper *_mapper;
};

#endif // DLGCOMPONENTEMATERIAL_H
