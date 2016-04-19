#ifndef EXECUTIONTASKITEMDELEGATE_H
#define EXECUTIONTASKITEMDELEGATE_H

#include <QObject>
#include <KDGanttItemDelegate>
#include <KDGanttStyleOptionGanttItem>

class ExecutionTaskItemDelegate : public KDGantt::ItemDelegate
{
public:
    explicit ExecutionTaskItemDelegate(QObject *parent = 0);

    void paintGanttItem(QPainter *painter, const KDGantt::StyleOptionGanttItem &opt, const QModelIndex &idx);

signals:

public slots:
};

#endif // EXECUTIONTASKITEMDELEGATE_H
