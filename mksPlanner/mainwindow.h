#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "views/tablewindow.h"
#include <QMdiSubWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void closeEvent(QCloseEvent *evt);
private:
    bool showSubWindow(const QString &windowName);
    void createSubWindow(const QString &windowName, QWidget *widget);

private slots:
    void on_actionSalir_triggered();

    void on_actionUnidades_triggered();

    void loadMaterialLibrary();
    void loadProject(const QString &fileName);

    void on_actionSave_Material_Library_triggered();

    void on_actionListado_triggered();

    void on_actionNuevo_triggered();

    void on_actionRubros_triggered();

    void on_actionCostos_triggered();

    void on_actionAbrir_triggered();

    void on_actionVerBibliotecaTareas_triggered();

    void on_actionVer_BibliotecaMateriales_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
