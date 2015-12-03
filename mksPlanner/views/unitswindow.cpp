#include "unitswindow.h"
#include "ui_unitswindow.h"

UnitsWindow::UnitsWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UnitsWindow)
{
    ui->setupUi(this);
}

UnitsWindow::~UnitsWindow()
{
    delete ui;
}
