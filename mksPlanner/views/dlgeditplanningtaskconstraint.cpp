#include "dlgeditplanningtaskconstraint.h"
#include "ui_dlgeditplanningtaskconstraint.h"
#include "models/planningtask.h"
#include "globalcontainer.h"
#include <QVariant>


DlgEditPlanningTaskConstraint::DlgEditPlanningTaskConstraint(PlanningTaskConstraintPtr constraint, int idProyecto, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgEditPlanningTaskConstraint)
{
    ui->setupUi(this);

    ui->cboTareaDestino->setModel(GlobalContainer::instance().projectLibrary(idProyecto)->model(Tables::PlanningTasks));
    ui->cboTareaDestino->setModelColumn(5);

    ui->cboTipo->addItem("Soft", 0);
    ui->cboTipo->addItem("Hard", 1);

    ui->cboRelationType->addItem("Termina T1 y comienza T2", 0);
    ui->cboRelationType->addItem("Termina T1 y Termina T2", 1);
    ui->cboRelationType->addItem("Comienza T1 y Comienza T2", 2);
    ui->cboRelationType->addItem("Comienza T1 y Termina T2", 3);

    ui->lblTareaOrigen->clear();
    PlanningTaskPtr p = qSharedPointerDynamicCast<PlanningTask>(GlobalContainer::instance().projectLibrary(idProyecto)->model(Tables::PlanningTasks)->getItem(constraint->idTask1()));
    if (!p.isNull())
    {
        ui->lblTareaOrigen->setText(p->name());
    }

    p = qSharedPointerDynamicCast<PlanningTask>(GlobalContainer::instance().projectLibrary(idProyecto)->model(Tables::PlanningTasks)->getItem(constraint->idTask2()));
    if (!p.isNull())
    {
        ui->cboTareaDestino->setCurrentIndex(ui->cboTareaDestino->findText(p->name()));
    }

    ui->cboRelationType->setCurrentIndex(ui->cboRelationType->findData(constraint->RelationType(), Qt::UserRole));
    ui->cboTipo->setCurrentIndex(ui->cboTipo->findData(constraint->Type()));

    _idProyecto = idProyecto;
    _constraint = constraint;
}

DlgEditPlanningTaskConstraint::~DlgEditPlanningTaskConstraint()
{
    delete ui;
}

void DlgEditPlanningTaskConstraint::on_buttonBox_accepted()
{
    EntityBasePtr entity = GlobalContainer::instance().projectLibrary(_idProyecto)->model(Tables::PlanningTasks)->getItemByRowid(ui->cboTareaDestino->currentIndex());
    _constraint->setIdTask2(entity->id());

    _constraint->setType(ui->cboTipo->currentData(Qt::UserRole).toInt());
    _constraint->setRelationType(ui->cboRelationType->currentData(Qt::UserRole).toInt());

    close();
}
