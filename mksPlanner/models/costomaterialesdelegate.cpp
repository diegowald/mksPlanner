#include "costomaterialesdelegate.h"
#include <QLineEdit>
#include <QDateEdit>

CostoMaterialesDelegate::CostoMaterialesDelegate(QObject *parent) : QStyledItemDelegate(parent)
{

}

QWidget *CostoMaterialesDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QWidget *w = NULL;
    switch (index.column())
    {
    case 2:
    {
        QLineEdit *edit = new QLineEdit(parent);
        w = edit;
        break;
    }
    case 3:
    {
        QDateEdit *edit = new QDateEdit(parent);
        w = edit;
        break;
    }
    default:
        break;
    }
    return w;
}


void CostoMaterialesDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    switch (index.column())
    {
    case 2:
    {
        double value = index.model()->data(index, Qt::EditRole).toDouble();
        QLineEdit *edit = static_cast<QLineEdit*>(editor);
        edit->setText(QString::number(value));
        break;
    }
    case 3:
    {
        QDate value = index.model()->data(index, Qt::EditRole).toDate();
        QDateEdit *edit = static_cast<QDateEdit*>(editor);
        edit->setDate(value);
        break;
    }
    default:
        break;
    }
}

void CostoMaterialesDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QVariant value;
    switch (index.column())
    {
    case 2:
    {
        QLineEdit *edit = static_cast<QLineEdit*>(editor);
        value = edit->text().toDouble();
        break;
    }
    case 3:
    {
        QDateEdit *edit = static_cast<QDateEdit*>(editor);
        value = edit->date();
        break;
    }
    default:
        break;
    }
    model->setData(index, value, Qt::EditRole);
}

void CostoMaterialesDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}
