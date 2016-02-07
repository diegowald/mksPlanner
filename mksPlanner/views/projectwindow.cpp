#include "projectwindow.h"
#include "ui_projectwindow.h"
#include <QTreeView>
#include "models/proyectomodel.h"
#include "globalcontainer.h"



ProjectWindow::ProjectWindow(const QString &windowTitle, int idInterno, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ProjectWindow)
{
    ui->setupUi(this);
    setWindowTitle(windowTitle);
    _mapper = NULL;
    _idInterno = idInterno;
}

ProjectWindow::~ProjectWindow()
{
    delete ui;
}


void ProjectWindow::setModel(ModelBase* model)
{
    _model = model;
    if (_mapper != NULL)
    {
        _mapper->deleteLater();
    }


    _mapper = new QDataWidgetMapper(this);
    _mapper->setModel(model);

    _mapper->addMapping(ui->txtPropietario, model->columnIndex("Propietario"));
    _mapper->addMapping(ui->txtDireccion, model->columnIndex("Direccion"));
    _mapper->addMapping(ui->txtEmail, model->columnIndex("Email"));
    _mapper->addMapping(ui->txtTelefono, model->columnIndex("Telefono"));
    _mapper->addMapping(ui->dateEstimacionInicio, model->columnIndex("Fecha estimada de Inicio"));
    _mapper->addMapping(ui->dateEstimacionFinalizacion, model->columnIndex("Fecha estimada de finalización"));

    _mapper->setCurrentIndex(0);
    _mapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);

    ui->tabWidget->setCurrentIndex(1);
    ui->tabWidget->setCurrentIndex(0);
    /* temporal es para ocultar los tabs que aun no han sido desarrollados */
    ui->tabWidget->removeTab(4);
    ui->tabWidget->removeTab(3);
    ui->tabWidget->removeTab(2);

    ui->lblFilename->setText(qobject_cast<ProyectoModel*>(model)->filename());
}

void ProjectWindow::setPlanningModel(ModelBase *model)
{
    _planningModel = new PlanningTaskModelAdapter(qobject_cast<PlanningTaskModel*>(model), this);
    ui->planningView->setModel(_planningModel);
    ui->planningView->setSelectionModel( new QItemSelectionModel(_planningModel));

    ui->planningView->leftView()->setHorizontalScrollBarPolicy( Qt::ScrollBarAsNeeded );
    ui->planningView->graphicsView()->setHorizontalScrollBarPolicy( Qt::ScrollBarAsNeeded );

    KDGantt::DateTimeGrid *grid = new KDGantt::DateTimeGrid();
    grid->setDayWidth(35);
    grid->setWeekStart(Qt::Sunday);
    grid->setScale(KDGantt::DateTimeGrid::ScaleDay);

    ui->planningView->setGrid(grid);

    QTreeView *tv = qobject_cast<QTreeView*>(ui->planningView->leftView());
    Q_ASSERT(tv);
}

void ProjectWindow::on_tabWidget_currentChanged(int index)
{
    ui->actionAddTask->setVisible(index == 1);
    ui->actionEdit_Task->setVisible(index == 1);
    ui->actionRemove_Task->setVisible(index == 1);
}

void ProjectWindow::on_actionAddTask_triggered()
{
    int rowCount = ui->planningView->model()->rowCount();

    QModelIndex index = ui->planningView->selectionModel()->currentIndex();


    if (!_planningModel->insertRow(rowCount, index.parent()))
        return;

    _planningModel->editEntity(rowCount);
}

void ProjectWindow::on_actionEdit_Task_triggered()
{
    QModelIndex index = ui->planningView->selectionModel()->currentIndex();
    _planningModel->editEntity(index.row());
}

void ProjectWindow::on_actionRemove_Task_triggered()
{
    QModelIndex index = ui->planningView->selectionModel()->currentIndex();
    _planningModel->removeEntity(this->window(), index.row());
}

void ProjectWindow::on_actionGuardar_cambios_triggered()
{
    GlobalContainer::instance().projectLibrary(_idInterno)->save();
}
