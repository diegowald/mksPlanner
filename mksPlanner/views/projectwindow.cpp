#include "projectwindow.h"
#include "ui_projectwindow.h"
#include <QTreeView>
#include "models/proyectomodel.h"
#include "globalcontainer.h"
#include "models/planningtask.h"
#include "models/proyecto.h"


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
    _mapper->addMapping(ui->txtPlazo, model->columnIndex("Plazo"));
    _mapper->addMapping(ui->txtCosto, model->columnIndex("Costo"));


    _mapper->setCurrentIndex(0);
    _mapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);

    ui->tabWidget->setCurrentIndex(1);
    ui->tabWidget->setCurrentIndex(0);
    /* temporal es para ocultar los tabs que aun no han sido desarrollados */
    ui->tabWidget->removeTab(4);
    ui->tabWidget->removeTab(3);

    ui->lblFilename->setText(qobject_cast<ProyectoModel*>(model)->filename());
    connect(model, &ModelBase::changed, this, &ProjectWindow::on_modelChanged);
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
    tv->setColumnHidden(1, true);
    tv->setColumnHidden(4, true);

    connect(tv, &QTreeView::doubleClicked, this, &ProjectWindow::on_TreeView_doubleClicked);
    ui->actionAddTask->setEnabled(model->canCreateEntity());
    connect(model, &ModelBase::changed, this, &ProjectWindow::on_PlanningModelChanged);
    updateEstimacionMateriales();
}

void ProjectWindow::setConstraintModel(ModelBase *model)
{
    _constraintModel = new PlanningTaskModelConstraintAdapter(_planningModel, model, this);
//    KDGantt::Constraint c;
    //_constraintModel = model;
    ui->planningView->setConstraintModel(_constraintModel);
}

void ProjectWindow::on_tabWidget_currentChanged(int index)
{
    ui->actionAddTask->setVisible(index == 1);
    ui->actionEdit_Task->setVisible(index == 1);
    ui->actionRemove_Task->setVisible(index == 1);
    ui->actionActionAddSubTask->setVisible(index == 1);
}

void ProjectWindow::on_actionAddTask_triggered()
{
    int rowCount = ui->planningView->model()->rowCount();

    QModelIndex index = ui->planningView->selectionModel()->currentIndex();


    if (!_planningModel->insertRow(rowCount, index.parent()))
        return;

    _planningModel->editEntity(rowCount);
}

void ProjectWindow::on_actionActionAddSubTask_triggered()
{
    QModelIndex idx = ui->planningView->selectionModel()->currentIndex();
    if (idx.isValid())
    {
        qDebug() << "MainWindow::slotToolsNewItem" << idx;
        if (!_planningModel->insertRow(1, _planningModel->index(idx.row(), 0, idx.parent())))
            return;

        //_planningModel->insertRows(0, 1, _planningModel->index(idx.row(), 0, idx.parent()));
        //_planningModel->editEntity(_planningModel->index(idx.row(), 0, idx.parent()).child(0, 0));
    }/* else {
        m_model->insertRows( 0, 1, m_view->rootIndex() );
    }*/
}

void ProjectWindow::on_actionEdit_Task_triggered()
{
    QModelIndex index = ui->planningView->selectionModel()->currentIndex();
    _planningModel->editEntity(index);
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

void ProjectWindow::on_modelChanged(Tables table)
{

}

void ProjectWindow::on_PlanningModelChanged(Tables table)
{
    ui->actionAddTask->setEnabled(_planningModel->canCreateEntity());
    updateEstimacionMateriales();
}

void ProjectWindow::on_TreeView_doubleClicked(const QModelIndex &index)
{
    if (index.isValid())
       _planningModel->editEntity(index);
}


void ProjectWindow::updateEstimacionMateriales()
{
    ui->tblEstimacionMateriales->setRowCount(0);
    ui->tblEstimacionMateriales->setColumnCount(3);
    ui->tblEstimacionMateriales->setHorizontalHeaderItem(0, new QTableWidgetItem(tr("Material")));
    ui->tblEstimacionMateriales->setHorizontalHeaderItem(1, new QTableWidgetItem(tr("Cantidad")));
    ui->tblEstimacionMateriales->setHorizontalHeaderItem(2, new QTableWidgetItem(tr("Unidad")));
    QMap<QString, double> results;
    int rowCount = _planningModel->rowCount(QModelIndex());
    for (int i = 0; i < rowCount; ++i)
    {
        EntityBasePtr entity = _planningModel->itemByRowId(i);
        PlanningTaskPtr pt = qSharedPointerDynamicCast<PlanningTask>(entity);
        QMap<QString, double> partialResult = pt->listadoMateriales();
        foreach (QString material, partialResult.keys())
        {
            if (!results.contains(material))
            {
                results[material] = partialResult[material];
            }
            else
            {
                results[material] += partialResult[material];
            }
        }
    }

    foreach (QString material, results.keys())
    {
        int row = ui->tblEstimacionMateriales->rowCount();
        ui->tblEstimacionMateriales->insertRow(row);
        ui->tblEstimacionMateriales->setItem(row, 0, new QTableWidgetItem(material));
        ui->tblEstimacionMateriales->setItem(row, 1, new QTableWidgetItem(QString::number(results[material])));
    }
}

