#ifndef MODELFROMTABLEWIDGET_H
#define MODELFROMTABLEWIDGET_H

#include <QObject>
#include <QTableWidget>
#include <QAbstractTableModel>

class ModelFromTableWidget : public QAbstractTableModel
{
    Q_OBJECT

public:
    ModelFromTableWidget(QTableWidget *widget, QObject *parent = 0);
    virtual ~ModelFromTableWidget();

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

private:
    QTableWidget *_widget;
};

#endif // MODELFROMTABLEWIDGET_H
