#ifndef EXECUTIONTASKITEMDELEGATE_H
#define EXECUTIONTASKITEMDELEGATE_H

#include <QObject>
#include <KDGanttItemDelegate>
#include <KDGanttStyleOptionGanttItem>
#include "models/executiontaskmodeladapter.h"

class ExecutionTaskItemDelegate : public KDGantt::ItemDelegate
{
public:
    explicit ExecutionTaskItemDelegate(ExecutionTaskModelAdapter *model, QObject *parent = 0);

    void paintGanttItem(QPainter *painter, const KDGantt::StyleOptionGanttItem &opt, const QModelIndex &idx);

signals:

public slots:
private:
    ExecutionTaskModelAdapter *_model;
};

#endif // EXECUTIONTASKITEMDELEGATE_H
