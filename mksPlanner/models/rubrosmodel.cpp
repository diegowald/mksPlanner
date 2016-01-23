#include "rubrosmodel.h"
#include "models/rubro.h"
#include <QSharedPointer>
#include "views/dlgeditrubro.h"


RubrosModel::RubrosModel(QObject *parent) : ModelBase("rubros", false, parent)
{

}


int RubrosModel::columnCount(const QModelIndex &/*parent*/) const
{
    return 4;
}

QVariant RubrosModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal)
        {
            switch (section)
            {
            case 0:
            {
                return QString("id");
                break;
            }
            case 1:
            {
                return QString("Nombre");
                break;
            }
            case 2:
            {
                return QString("Descripción");
                break;
            }
            case 3:
            {
                return QString("Contiene tareas");
                break;
            }
            default:
                break;
            }
        }
        return section;
    }
    return QAbstractItemModel::headerData(section, orientation, role);
}


QString RubrosModel::_getSQLRead() const
{
    return "select * from rubros;";
}

int RubrosModel::_loadEntity(QSqlRecord record)
{
    int id = record.value(record.indexOf("id")).toInt();
    QString nombre = record.value(record.indexOf("nombre")).toString();
    QString descripcion = record.value(record.indexOf("descripcion")).toString();
    bool isTask = record.value(record.indexOf("isTask")).toBool();
    EntityBasePtr entity = RubroPtr::create(id, nombre, descripcion, isTask);
    addEntity(entity);
    return id;
}


/*
bool UnitsModel::removeRow(int row, const QModelIndex &parent)
{
    _entities[_entityMapping.at(row)]->deleteEntity();
    _entityMapping.removeAt(row);
}
*/

EntityBasePtr RubrosModel::internalCreateEntity(int assignedId)
{
    return RubroPtr::create(assignedId);
}


void RubrosModel::editEntity(int row)
{
    DlgEditRubro dlg(this, row);
    dlg.exec();
}
