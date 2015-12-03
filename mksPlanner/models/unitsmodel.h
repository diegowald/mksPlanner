#ifndef UNITSMODEL_H
#define UNITSMODEL_H

#include <QAbstractTableModel>

class UnitsModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    UnitsModel(QObject *parent = 0);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);

    Qt::ItemFlags flags(const QModelIndex &index) const;
signals:

public slots:

private:
    QString _value;
};

#endif // UNITSMODEL_H
