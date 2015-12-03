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

private:
    Ui::UnitsWindow *ui;
    UnitsModel _model;
};

#endif // UNITSWINDOW_H
