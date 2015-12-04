#ifndef DLGUNITEDITOR_H
#define DLGUNITEDITOR_H

#include <QDialog>

#include <QDataWidgetMapper>
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

private:
    Ui::dlgUnitEditor *ui;
    UnitsModel *_model;
    QDataWidgetMapper *_mapper;
};

#endif // DLGUNITEDITOR_H
