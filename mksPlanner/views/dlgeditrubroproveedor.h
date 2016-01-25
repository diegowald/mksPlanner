#ifndef DLGEDITRUBROPROVEEDOR_H
#define DLGEDITRUBROPROVEEDOR_H

#include <QDialog>
#include "models/rubrosproveedoresmodel.h"

namespace Ui {
class DlgEditRubroProveedor;
}

class DlgEditRubroProveedor : public QDialog
{
    Q_OBJECT

public:
    explicit DlgEditRubroProveedor(int idProveedor, RubrosProveedoresModel *model, int selectedEntity,  QWidget *parent = 0);
    ~DlgEditRubroProveedor();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::DlgEditRubroProveedor *ui;
    RubrosProveedoresModel *_model;
    EntityBasePtr _entity;
};

#endif // DLGEDITRUBROPROVEEDOR_H

/*

#include <QDialog>
#include <QDataWidgetMapper>
#endif // DLGTASKPROVEEDOREDIT_H
*/
