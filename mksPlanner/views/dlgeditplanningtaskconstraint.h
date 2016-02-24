#ifndef DLGEDITPLANNINGTASKCONSTRAINT_H
#define DLGEDITPLANNINGTASKCONSTRAINT_H

#include <QDialog>
#include "models/planningtaskconstraint.h"

namespace Ui {
class DlgEditPlanningTaskConstraint;
}

class DlgEditPlanningTaskConstraint : public QDialog
{
    Q_OBJECT

public:
    explicit DlgEditPlanningTaskConstraint(PlanningTaskConstraintPtr constraint, int idProyecto, QWidget *parent = 0);
    ~DlgEditPlanningTaskConstraint();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::DlgEditPlanningTaskConstraint *ui;
    PlanningTaskConstraintPtr _constraint;
    int _idProyecto;
};

#endif // DLGEDITPLANNINGTASKCONSTRAINT_H
