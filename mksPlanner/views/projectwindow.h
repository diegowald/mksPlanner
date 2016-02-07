#ifndef PROJECTWINDOW_H
#define PROJECTWINDOW_H

#include <QMainWindow>
#include <QDataWidgetMapper>

#include "models/modelbase.h"
#include "models/planningtaskmodeladapter.h"
namespace Ui {
class ProjectWindow;
}

class ProjectWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ProjectWindow(const QString &windowTitle, int idInterno, QWidget *parent = 0);
    ~ProjectWindow();

    void setModel(ModelBase* model);
    void setPlanningModel(ModelBase *model);


private slots:
    void on_tabWidget_currentChanged(int index);

    void on_actionAddTask_triggered();

    void on_actionEdit_Task_triggered();

    void on_actionRemove_Task_triggered();

    void on_actionGuardar_cambios_triggered();

private:
    Ui::ProjectWindow *ui;
    ModelBase* _model;
    QDataWidgetMapper *_mapper;
    PlanningTaskModelAdapter *_planningModel;
    int _idInterno;
};

#endif // PROJECTWINDOW_H
