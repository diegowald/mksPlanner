#include "dlgsplitexecutiontask.h"
#include "ui_dlgsplitexecutiontask.h"
#include "models/executiontask.h"
#include "models/proveedor.h"


DlgSplitExecutionTask::DlgSplitExecutionTask(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgSplitExecutionTask)
{
    ui->setupUi(this);
    ui->pctRealizdo->setMinimum(0.0);
    ui->pctRealizdo->setMaximum(100.0);
    _cantRealizada = 0.;
    _cantTotal = 0.;
}

DlgSplitExecutionTask::~DlgSplitExecutionTask()
{
    delete ui;
}

QDateTime DlgSplitExecutionTask::dateTime() const
{
    return ui->dateFechaSplit->dateTime();
}

double DlgSplitExecutionTask::pct() const
{
    return ui->pctRealizdo->value();
}

void DlgSplitExecutionTask::setDateTime(QDateTime &value)
{
    ui->dateFechaSplit->setDateTime(value);
}

void DlgSplitExecutionTask::setPct(double value)
{
    ui->pctRealizdo->setValue(value);
}

void DlgSplitExecutionTask::setExecutionTask(EntityBasePtr entity)
{
    ExecutionTaskPtr et = qSharedPointerDynamicCast<ExecutionTask>(entity);
    ui->lblTarea->setText(et->name());

    ProveedorPtr p = qSharedPointerDynamicCast<Proveedor>(et->proveedor());
    ui->lblProveedor->setText(p->name());
}

void DlgSplitExecutionTask::setCantidadTotal(double value)
{
    _cantTotal = value;
    ui->lblCantidad->setText(QString::number(_cantTotal));
    if (_cantTotal > 0)
    {
        ui->pctRealizdo->setMinimum(100.0 * _cantRealizada / _cantTotal);
    }
}

void DlgSplitExecutionTask::setCantidadRealizada(double value)
{
    _cantRealizada = value;
    if (_cantTotal > 0)
    {
        ui->pctRealizdo->setMinimum(100.0 * _cantRealizada / _cantTotal);
    }
}
