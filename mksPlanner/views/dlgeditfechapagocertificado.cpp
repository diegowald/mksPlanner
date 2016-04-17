#include "dlgeditfechapagocertificado.h"
#include "ui_dlgeditfechapagocertificado.h"


dlgEditFechaPagoCertificado::dlgEditFechaPagoCertificado(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgEditFechaPagoCertificado)
{
    ui->setupUi(this);
    ui->dateEdit->setDate(QDate::currentDate());
}

dlgEditFechaPagoCertificado::~dlgEditFechaPagoCertificado()
{
    delete ui;
}

QDate dlgEditFechaPagoCertificado::fechaPago() const
{
    return ui->dateEdit->date();
}
