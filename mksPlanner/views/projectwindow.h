#ifndef PROJECTWINDOW_H
#define PROJECTWINDOW_H

#include <QMainWindow>
#include <QDataWidgetMapper>

#include "models/modelbase.h"

namespace Ui {
class ProjectWindow;
}

class ProjectWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ProjectWindow(const QString &windowTitle, QWidget *parent = 0);
    ~ProjectWindow();

    void setModel(ModelBase* model);
    void setPlanningModel(ModelBase *model);


private slots:
    void on_tabWidget_currentChanged(int index);

private:
    Ui::ProjectWindow *ui;
    ModelBase* _model;
    QDataWidgetMapper *_mapper;

    ModelBase* _planningModel;
};

#endif // PROJECTWINDOW_H
