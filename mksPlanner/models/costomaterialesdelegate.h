#ifndef COSTOMATERIALESDELEGATE_H
#define COSTOMATERIALESDELEGATE_H

#include <QStyledItemDelegate>

class CostoMaterialesDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit CostoMaterialesDelegate(QObject *parent = 0);


    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const Q_DECL_OVERRIDE;

    void setEditorData(QWidget *editor, const QModelIndex &index) const Q_DECL_OVERRIDE;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const Q_DECL_OVERRIDE;

    void updateEditorGeometry(QWidget *editor,
        const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;

signals:

public slots:
};

#endif // COSTOMATERIALESDELEGATE_H

