#ifndef DLGEDITCERTIFICACION_H
#define DLGEDITCERTIFICACION_H

#include <QDialog>

#include "models/certificacionesmodel.h"

namespace Ui {
class dlgEditCertificacion;
}

class dlgEditCertificacion : public QDialog
{
    Q_OBJECT

public:
    explicit dlgEditCertificacion(CertificacionesModel *model, int selectedEntity, QWidget *parent = 0);
    ~dlgEditCertificacion();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::dlgEditCertificacion *ui;
    CertificacionesModel *_model;
    EntityBasePtr _entity;
};

#endif // DLGEDITCERTIFICACION_H
