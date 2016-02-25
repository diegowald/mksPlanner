#ifndef DLGUNITEDITOR_H
#define DLGUNITEDITOR_H

#include <QDialog>

#include "models/unitsmodel.h"

namespace Ui {
class dlgUnitEditor;
}

class dlgUnitEditor : public QDialog
{
    Q_OBJECT

public:
    explicit dlgUnitEditor(UnitsModel *model, int selectedEntity, QWidget *parent = 0);
    ~dlgUnitEditor();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::dlgUnitEditor *ui;
    UnitsModel *_model;
    EntityBasePtr _entity;
};

#endif // DLGUNITEDITOR_H
