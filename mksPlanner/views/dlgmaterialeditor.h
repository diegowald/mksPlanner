#ifndef DLGMATERIALEDITOR_H
#define DLGMATERIALEDITOR_H

#include <QDialog>
#include "models/materialesbasemodel.h"


namespace Ui {
class dlgMaterialEditor;
}

class dlgMaterialEditor : public QDialog
{
    Q_OBJECT

public:
    explicit dlgMaterialEditor(MaterialesBaseModel *model, int row, bool isTask, QWidget *parent = 0);
    ~dlgMaterialEditor();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::dlgMaterialEditor *ui;
    MaterialesBaseModel *_model;
    EntityBasePtr _entity;
    IModel* _rubroFilter;
    bool _isTask;
};

#endif // DLGMATERIALEDITOR_H
