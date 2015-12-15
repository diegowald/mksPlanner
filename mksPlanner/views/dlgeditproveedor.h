#ifndef DLGEDITPROVEEDOR_H
#define DLGEDITPROVEEDOR_H

#include <QDialog>
#include "models/proveedoresmodel.h"
#include <QDataWidgetMapper>

namespace Ui {
class dlgEditProveedor;
}

class dlgEditProveedor : public QDialog
{
    Q_OBJECT

public:
    explicit dlgEditProveedor(ProveedoresModel*model, int row, QWidget *parent = 0);
    ~dlgEditProveedor();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::dlgEditProveedor *ui;
    ProveedoresModel *_model;
    QDataWidgetMapper *_mapper;
};



#endif // DLGEDITPROVEEDOR_H
