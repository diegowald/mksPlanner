#ifndef QCANTIDADVALIDATOR_H
#define QCANTIDADVALIDATOR_H

#include <QObject>
#include <QValidator>

class QCantidadValidator : public QObject
{
    Q_OBJECT
public:
    explicit QCantidadValidator(QObject *parent = 0);

signals:

public slots:
};

#endif // QCANTIDADVALIDATOR_H
