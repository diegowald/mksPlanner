#include "calculadoramaterialeswindow.h"
#include "ui_calculadoramaterialeswindow.h"

CalculadoraMaterialesWindow::CalculadoraMaterialesWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CalculadoraMaterialesWindow)
{
    ui->setupUi(this);
}

CalculadoraMaterialesWindow::~CalculadoraMaterialesWindow()
{
    delete ui;
}
