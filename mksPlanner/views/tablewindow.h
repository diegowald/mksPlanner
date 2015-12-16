#ifndef UNITSWINDOW_H
#define UNITSWINDOW_H

#include <QMainWindow>
//#include "models/unitsmodel.h"
#include "models/modelbase.h"

namespace Ui {
class TableWindow;
}

class TableWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TableWindow(const QString &windowTitle, QWidget *parent = 0);
    ~TableWindow();

    void setModel(ModelBase* model);

private slots:
    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_actionCreate_triggered();

    void on_actionEdit_triggered();

    void on_actionRemove_triggered();

private:
    Ui::TableWindow *ui;
    ModelBase* _model;
};

#endif // UNITSWINDOW_H
