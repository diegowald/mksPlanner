#ifndef MATERIALESMODEL_H
#define MATERIALESMODEL_H

#include <QObject>
#include "models/modelbase.h"

class MaterialesModel : public ModelBase
{
    Q_OBJECT
public:
    explicit MaterialesModel(QObject *parent = 0);
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    virtual void editEntity(int row);

protected:
    virtual QString _getSQLRead() const;
    virtual void _loadEntity(QSqlRecord record);
    virtual EntityBasePtr createEntity();

signals:

public slots:
};

#endif // MATERIALESMODEL_H
