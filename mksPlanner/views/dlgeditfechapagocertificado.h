#ifndef DLGEDITCERTIFICACION_H
#define DLGEDITCERTIFICACION_H

#include <QDialog>

namespace Ui {
class dlgEditFechaPagoCertificado;
}

class dlgEditFechaPagoCertificado : public QDialog
{
    Q_OBJECT

public:
    explicit dlgEditFechaPagoCertificado(QWidget *parent = 0);
    ~dlgEditFechaPagoCertificado();

    QDate fechaPago() const;

private:
    Ui::dlgEditFechaPagoCertificado *ui;
};

#endif // DLGEDITCERTIFICACION_H
