#include "dlgEditCertificacion.h"
#include "ui_dlgEditCertificacion.h"
#include "models/certificacion.h"


dlgEditCertificacion::dlgEditCertificacion(CertificacionesModel *model, int selectedEntity, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgEditCertificacion)
{
    _model = model;
    ui->setupUi(this);

    _entity = model->getItemByRowid(selectedEntity);
    CertificacionPtr cert = qSharedPointerDynamicCast<Certificacion>(_entity);
    ui->dateEdit->setDate(cert->fechaCertificacion().date());
}

dlgEditCertificacion::~dlgEditCertificacion()
{
    delete ui;
}

void dlgEditCertificacion::on_buttonBox_accepted()
{
    CertificacionPtr cert = qSharedPointerDynamicCast<Certificacion>(_entity);
    cert->setFechaCertificacion(ui->dateEdit->dateTime());

    close();
}
