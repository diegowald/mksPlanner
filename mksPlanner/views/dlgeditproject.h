#ifndef DLGEDITPROJECT_H
#define DLGEDITPROJECT_H

#include <QDialog>
#include "models/proyectomodel.h"


namespace Ui {
class dlgEditProject;
}

class dlgEditProject : public QDialog
{
    Q_OBJECT

public:
    explicit dlgEditProject(ProyectoModel*model, int row, QWidget *parent = 0);
    ~dlgEditProject();

private:
    Ui::dlgEditProject *ui;
};

#endif // DLGEDITPROJECT_H
