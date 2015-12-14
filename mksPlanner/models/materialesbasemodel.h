#ifndef MATERIALESBASEMODEL_H
#define MATERIALESBASEMODEL_H

#include <QObject>
#include "models/modelbase.h"

class MaterialesBaseModel : public ModelBase
{
    Q_OBJECT
public:
    explicit MaterialesBaseModel(bool filterByTask, QObject *parent = 0);
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    virtual void editEntity(int row);

protected:
    virtual QString _getSQLRead() const;
    virtual int _loadEntity(QSqlRecord record);

signals:

public slots:

private:
    bool _filterByTask;
};

#endif // MATERIALESBASEMODEL_H
