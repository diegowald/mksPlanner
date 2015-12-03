#include "unitswindow.h"
#include "ui_unitswindow.h"

UnitsWindow::UnitsWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UnitsWindow)
{
    ui->setupUi(this);
    ui->tableView->setModel(&_model);
}

UnitsWindow::~UnitsWindow()
{
    delete ui;
}
