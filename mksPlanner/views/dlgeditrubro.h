#ifndef DLGEDITRUBRO_H
#define DLGEDITRUBRO_H

#include <QDialog>
#include <QDataWidgetMapper>
#include "models/rubrosmodel.h"
#include "models/entitybase.h"

namespace Ui {
class DlgEditRubro;
}

class DlgEditRubro : public QDialog
{
    Q_OBJECT

public:
    explicit DlgEditRubro(RubrosModel *model, int selectedEntity, QWidget *parent = 0);
    ~DlgEditRubro();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::DlgEditRubro *ui;
    RubrosModel *_model;
    QDataWidgetMapper *_mapper;
    EntityBasePtr _entity;
};

#endif // DLGEDITRUBRO_H
