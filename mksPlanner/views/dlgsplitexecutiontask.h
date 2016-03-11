#ifndef DLGSPLITEXECUTIONTASK_H
#define DLGSPLITEXECUTIONTASK_H

#include <QDialog>
#include "models/entitybase.h"
namespace Ui {
class DlgSplitExecutionTask;
}

class DlgSplitExecutionTask : public QDialog
{
    Q_OBJECT

public:
    explicit DlgSplitExecutionTask(QWidget *parent = 0);
    ~DlgSplitExecutionTask();

    QDateTime dateTime() const;
    double pct() const;

    void setDateTime(QDateTime &value);
    void setPct(double value);
    void setExecutionTask(EntityBasePtr entity);
    void setCantidadTotal(double value);
    void setCantidadRealizada(double value);


private:
    Ui::DlgSplitExecutionTask *ui;
    double _cantTotal;
    double _cantRealizada;
};

#endif // DLGSPLITEXECUTIONTASK_H
