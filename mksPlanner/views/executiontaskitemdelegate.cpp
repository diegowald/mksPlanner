#include "executiontaskitemdelegate.h"
#include <KDGanttStyleOptionGanttItem>
#include <QPainter>
#include <QApplication>
#include "models/executiontask.h"
#include "models/executiontaskmodel.h"

ExecutionTaskItemDelegate::ExecutionTaskItemDelegate(ExecutionTaskModelAdapter *model, QObject *parent) : ItemDelegate(parent)
{
    _model = model;
}

void ExecutionTaskItemDelegate::paintGanttItem(QPainter *painter, const KDGantt::StyleOptionGanttItem &opt, const QModelIndex &idx)
{
    painter->setRenderHints(QPainter::Antialiasing);
    if (!idx.isValid())
    {
        return;
    }

    ExecutionTaskPtr ex = qSharedPointerDynamicCast<ExecutionTask>(_model->innerModel()->getItemByRowid(idx.row()));


    KDGantt::ItemType type = static_cast<KDGantt::ItemType>(
                idx.model()->data(idx, KDGantt::ItemTypeRole).toInt());

    QBrush brush = defaultBrush(type);
    if (ex->idPlanningTask() == -1)
    {
        // Brushes
        QLinearGradient taskgrad( 0., 0., 0., QApplication::fontMetrics().height() );
        taskgrad.setColorAt(0., Qt::red);
        taskgrad.setColorAt(1., Qt::darkRed);
        brush = taskgrad;

        QString txt = idx.model()->data(idx, Qt::DisplayRole).toString();
        QRectF itemRect = opt.itemRect;
        QRectF boundingRect = opt.boundingRect;
        boundingRect.setY(itemRect.y());
        boundingRect.setHeight(itemRect.height());




        if (itemRect.isValid())
        {
            QLinearGradient selectedGrad(0., 0., 0., QApplication::fontMetrics().height());
            selectedGrad.setColorAt(0., Qt::red);
            selectedGrad.setColorAt(1., Qt::darkRed);
            brush = QBrush(selectedGrad);
            painter->save();
            painter->setPen(defaultPen(type));
            painter->setBrush(brush);
            painter->setBrushOrigin(itemRect.topLeft());
            // TODO
            //qreal pw = painter->pen().width()/2.;
            //pw -= 1;
            QRectF r = itemRect;
            r.translate( 0., r.height()/6. );
            r.setHeight( 2.*r.height()/3. );
            painter->setBrushOrigin( itemRect.topLeft() );
            painter->save();
            painter->translate( 0.5, 0.5 );
            painter->drawRect( r );
            bool ok;
            qreal completion = idx.model()->data(idx, KDGantt::TaskCompletionRole).toReal(&ok);
            if (ok)
            {
                qreal h = r.height();
                QRectF cr(r.x(), r.y() + h / 4.,
                          r.width() * completion / 100., h / 2. + 1 /*??*/ );
                QColor compcolor( painter->pen().color() );
                compcolor.setAlpha( 150 );
                painter->fillRect( cr, compcolor );
            }
            painter->restore();
            Qt::Alignment ta;
            bool display = true;
            switch(opt.displayPosition)
            {
            case KDGantt::StyleOptionGanttItem::Left:
                ta = Qt::AlignLeft;
                break;
            case KDGantt::StyleOptionGanttItem::Right:
                ta = Qt::AlignRight;
                break;
            case KDGantt::StyleOptionGanttItem::Center:
                ta = Qt::AlignCenter;
                break;
            case KDGantt::StyleOptionGanttItem::Hidden:
                display = false;
                break;
            }
            if (display)
                painter->drawText(boundingRect, ta, txt);

            painter->restore();
        }

    }
    else
    {
        KDGantt::ItemDelegate::paintGanttItem(painter, opt, idx);
    }
}
