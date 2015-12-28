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


private:
    Ui::ProjectWindow *ui;
    ModelBase* _model;
    QDataWidgetMapper *_mapper;
};

#endif // PROJECTWINDOW_H
