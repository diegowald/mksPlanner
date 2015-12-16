#ifndef CALCULADORAMATERIALESWINDOW_H
#define CALCULADORAMATERIALESWINDOW_H

#include <QMainWindow>

namespace Ui {
class CalculadoraMaterialesWindow;
}

class CalculadoraMaterialesWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CalculadoraMaterialesWindow(QWidget *parent = 0);
    ~CalculadoraMaterialesWindow();

private:
    Ui::CalculadoraMaterialesWindow *ui;
};

#endif // CALCULADORAMATERIALESWINDOW_H
