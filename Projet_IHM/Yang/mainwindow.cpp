#include "mainwindow.h"
#include "petitwindow.h"
#include "treemodel.h"
#include <QWidget>
#include <qpushbutton.h>
#include <QDockWidget>
#include <QTextEdit>
#include <QLayout>

#include <QFile>
#include <QTreeWidget>
#include <QVariant>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    setWindowTitle(QString::fromUtf8("MainWindow"));

    resize(800, 600);


    /************BAR DE MENU ****************/
    this->statusBar();
    QMenuBar* barmenu = this->menuBar();
    QMenu* fichier = barmenu->addMenu(tr("&Fichier"));
    QMenu* attribut = barmenu->addMenu("&Attribut");
    QMenu* forme = barmenu->addMenu("&Forme");

    barmenu->setNativeMenuBar(false);


     /************ ONGLETS************/

      QWidget *centralWidget = new QWidget(this);
      QTabWidget *tabs = new QTabWidget(centralWidget);
    setCentralWidget(centralWidget);

    tabs->setFixedHeight(70);

    tabs->addTab(new QWidget(),"Fichier");
    tabs->addTab(new QWidget(),"Aspect");
    tabs->addTab(new QWidget(),"Format");
    tabs->setTabsClosable(true);

    /*********** ZONE EDITION *****/

    QVBoxLayout* zoneedition = new QVBoxLayout;
    QPushButton * bouton = new QPushButton("Bonjour");
    petitwindow* petitefenetre = new petitwindow();
    zoneedition -> addWidget(petitefenetre);
    zoneedition->addWidget(bouton);


    /******** CENTRAL WIDGET = onglets + zoneEdition*******/

    QVBoxLayout* layoutV = new QVBoxLayout;
    layoutV->addWidget(tabs);
    layoutV->addLayout(zoneedition);

    centralWidget->setLayout(layoutV);

    /********** DOCK WIDGET DE GAUCHE = Liste *************/

    QDockWidget * dockgauche = new QDockWidget("Hierarchie", this);
    dockgauche->setAllowedAreas(Qt::LeftDockWidgetArea);
    this->addDockWidget(Qt::LeftDockWidgetArea,dockgauche);

    dockgauche->setMinimumSize(200,600);
    dockgauche->setMaximumSize(400,600);

    QTreeWidget *treeWidget = new QTreeWidget(dockgauche);
    treeView = new QTreeView(treeWidget);

    treeView->setObjectName(tr("treeView"));
    treeView->setAlternatingRowColors(true);
    treeView->setSelectionBehavior(QAbstractItemView::SelectItems);
    treeView->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    treeView->setMinimumSize(200,600);
    treeView->setMaximumSize(400,600);
    treeView->setAnimated(false);
    treeView->setAllColumnsShowFocus(true);


    dockgauche->setWidget(treeWidget);


    /********** Define Actions *****************/
    insertRowAct = new QAction(tr("&InsertRow"),this);
    insertRowAct->setObjectName(tr("insertRowAct"));
    removeRowAct = new QAction(tr("&RemoveRow"),this);
    removeRowAct->setObjectName(tr("removeRowAct"));
    insertChildAct = new QAction(tr("&InsertChild"),this);
    insertChildAct->setObjectName(tr("insertChildAct"));

    exitAct = new QAction(tr("&Exit"),this);
    exitAct->setObjectName(tr("exitAct"));

    /*********** Add Actions **************/
    fichier->addAction(insertRowAct);
    fichier->addAction(removeRowAct);
    fichier->addSeparator();
    fichier->addAction(insertChildAct);
    fichier->addSeparator();
    fichier->addAction(exitAct);

    /********** Setup TreeList *************/
    QStringList headers;
    headers << tr("Title") << tr("Date");

    QFile file(":/default.txt");
    file.open(QIODevice::ReadOnly);
    TreeModel *model = new TreeModel(headers, file.readAll());
    file.close();

    treeView->setModel(model);

    for (int column = 0; column < model->columnCount(); ++column)
        treeView->resizeColumnToContents(column);

    connect(treeView->selectionModel(),
            SIGNAL(selectionChanged(const QItemSelection &,
                                    const QItemSelection &)),
            this, SLOT(updateActions()));

    connect(fichier, SIGNAL(aboutToShow()), this, SLOT(updateActions()));
    connect(insertRowAct, SIGNAL(triggered()), this, SLOT(insertRow()));
    connect(removeRowAct, SIGNAL(triggered()), this, SLOT(removeRow()));
    connect(insertChildAct, SIGNAL(triggered()), this, SLOT(insertChild()));

    connect(exitAct, SIGNAL(triggered()), qApp, SLOT(quit()));

    updateActions();
}

void MainWindow::insertChild()
{
    QModelIndex index = treeView->selectionModel()->currentIndex();
    QAbstractItemModel *model = treeView->model();

    if (model->columnCount(index) == 0) {
        if (!model->insertColumn(0, index))
            return;
    }

    if (!model->insertRow(0, index))
        return;

    for (int column = 0; column < model->columnCount(index); ++column) {
        QModelIndex child = model->index(0, column, index);
        model->setData(child, QVariant("[No data]"), Qt::EditRole);
        if (!model->headerData(column, Qt::Horizontal).isValid())
            model->setHeaderData(column, Qt::Horizontal, QVariant("[No header]"), Qt::EditRole);
    }

    treeView->selectionModel()->setCurrentIndex(model->index(0, 0, index),
                                            QItemSelectionModel::ClearAndSelect);
    updateActions();
}

void MainWindow::insertRow()
{
    QModelIndex index = treeView->selectionModel()->currentIndex();
    QAbstractItemModel *model = treeView->model();

    if (!model->insertRow(index.row()+1, index.parent()))
        return;

    updateActions();

    for (int column = 0; column < model->columnCount(index.parent()); ++column) {
        QModelIndex child = model->index(index.row()+1, column, index.parent());
        model->setData(child, QVariant("[No data]"), Qt::EditRole);
    }
}

void MainWindow::removeRow()
{
    QModelIndex index = treeView->selectionModel()->currentIndex();
    QAbstractItemModel *model = treeView->model();
    if (model->removeRow(index.row(), index.parent()))
        updateActions();
}

void MainWindow::updateActions()
{
    bool hasSelection = !treeView->selectionModel()->selection().isEmpty();
    removeRowAct->setEnabled(hasSelection);

    bool hasCurrent = treeView->selectionModel()->currentIndex().isValid();
    insertRowAct->setEnabled(hasCurrent);

    if (hasCurrent) {
        treeView->closePersistentEditor(treeView->selectionModel()->currentIndex());

        int row = treeView->selectionModel()->currentIndex().row();
        int column = treeView->selectionModel()->currentIndex().column();
        if (treeView->selectionModel()->currentIndex().parent().isValid())
            statusBar()->showMessage(tr("Position: (%1,%2)").arg(row).arg(column));
        else
            statusBar()->showMessage(tr("Position: (%1,%2) in top level").arg(row).arg(column));
    }
}



MainWindow::~MainWindow()
{
    delete ui;
}
