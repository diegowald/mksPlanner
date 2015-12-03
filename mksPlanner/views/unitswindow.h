#ifndef UNITSWINDOW_H
#define UNITSWINDOW_H

#include <QMainWindow>

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
};

#endif // UNITSWINDOW_H
