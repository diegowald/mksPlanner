#include "projectwindow.h"
#include "ui_projectwindow.h"
#include <QTreeView>

ProjectWindow::ProjectWindow(const QString &windowTitle, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ProjectWindow)
{
    ui->setupUi(this);
    setWindowTitle(windowTitle);
    _mapper = NULL;
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
    _mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
}

void ProjectWindow::setPlanningModel(ModelBase *model)
{
    _planningModel = new PlanningTaskModelAdapter(qobject_cast<PlanningTaskModel*>(model), this);
    ui->planningView->setModel(_planningModel);
    ui->planningView->setSelectionModel( new QItemSelectionModel(_planningModel));

    // slotToolsNewItem();
//    ui->planningView->leftView()->setItemDelegateForColumn( 1, new MyItemDelegate( this ) );
    ui->planningView->leftView()->setHorizontalScrollBarPolicy( Qt::ScrollBarAsNeeded );
    ui->planningView->graphicsView()->setHorizontalScrollBarPolicy( Qt::ScrollBarAsNeeded );

    KDGantt::DateTimeGrid *grid = new KDGantt::DateTimeGrid();
    grid->setDayWidth(70);
    ui->planningView->setGrid(grid);

    QTreeView *tv = qobject_cast<QTreeView*>(ui->planningView->leftView());
    Q_ASSERT(tv);
/*    tv->setColumnHidden(0, true);
    tv->setColumnHidden(1, true);
    tv->setColumnHidden(2, true);
    tv->setColumnHidden(3, true);*/
}

void ProjectWindow::on_tabWidget_currentChanged(int index)
{
    switch (index)
    {
    case 0:
        break;
    default:
        break;
    }
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
