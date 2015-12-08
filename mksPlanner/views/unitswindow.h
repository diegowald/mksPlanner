#ifndef UNITSWINDOW_H
#define UNITSWINDOW_H

#include <QMainWindow>
#include "models/unitsmodel.h"

namespace Ui {
class UnitsWindow;
}

class UnitsWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit UnitsWindow(QWidget *parent = 0);
    ~UnitsWindow();

    void save();

private slots:
    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_actionCreate_triggered();

    void on_actionEdit_triggered();

    void on_actionRemove_triggered();

private:
    Ui::UnitsWindow *ui;
    UnitsModel *_model;
};

#endif // UNITSWINDOW_H
