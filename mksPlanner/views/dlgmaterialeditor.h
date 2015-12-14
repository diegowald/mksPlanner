#ifndef DLGMATERIALEDITOR_H
#define DLGMATERIALEDITOR_H

#include <QDialog>
#include "models/materialesbasemodel.h"
#include <QDataWidgetMapper>


namespace Ui {
class dlgMaterialEditor;
}

class dlgMaterialEditor : public QDialog
{
    Q_OBJECT

public:
    explicit dlgMaterialEditor(MaterialesBaseModel *model, int row, QWidget *parent = 0);
    ~dlgMaterialEditor();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::dlgMaterialEditor *ui;
    MaterialesBaseModel *_model;
    QDataWidgetMapper *_mapper;
};

#endif // DLGMATERIALEDITOR_H
