#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "views/unitswindow.h"
#include <QMdiSubWindow>
#include "persistance/materialslibrary.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionSalir_triggered();

    void on_actionUnidades_triggered();

    void loadMaterialLibrary();
    void loadProject(const QString &fileName);

    void on_actionSave_Material_Library_triggered();

private:
    Ui::MainWindow *ui;
    QMdiSubWindow *unitsSubWindow;
    MaterialsLibrary _materialsLibrary;

};

#endif // MAINWINDOW_H
