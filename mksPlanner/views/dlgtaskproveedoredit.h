#ifndef DLGTASKPROVEEDOREDIT_H
#define DLGTASKPROVEEDOREDIT_H

#include <QDialog>
#include <QDataWidgetMapper>
#include "models/tareasproveedoresmodel.h"

namespace Ui {
class dlgTaskProveedorEdit;
}

class dlgTaskProveedorEdit : public QDialog
{
    Q_OBJECT

public:
    explicit dlgTaskProveedorEdit(int idProveedor, TareasProveedoresModel *model, int selectedEntity, QWidget *parent = 0);
    ~dlgTaskProveedorEdit();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::dlgTaskProveedorEdit *ui;
    TareasProveedoresModel *_model;
    EntityBasePtr _entity;
};

#endif // DLGTASKPROVEEDOREDIT_H
