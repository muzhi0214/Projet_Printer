#include "mainwindow.h"
#include "petitwindow.h"
#include "ui_mainwindow.h"
#include "treemodel.h"
#include "fichier.h"
#include "aspect.h"
#include <QWidget>
#include <qpushbutton.h>
#include <QDockWidget>
#include <QTextEdit>
#include <QLayout>
#include <Qcolor>

#include <QFile>
#include <QTreeWidget>
#include <QVariant>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)



{


    setWindowTitle(QString::fromUtf8("MainWindow"));
    //this->showFullScreen();
    //showFullScreen();
    resize(1200,600);
    //showMinimized();


    /************BAR DE MENU ****************/
    this->statusBar();
    QMenuBar* barmenu = menuBar();
    barmenu->setNativeMenuBar(false);
    QMenu* menufichier = barmenu->addMenu("&Fichier");
    QMenu* menuattribut = barmenu->addMenu("&Attribut");
    QMenu* menuforme = barmenu->addMenu("&Forme");


     QWidget *centralWidget = new QWidget(this);
     setCentralWidget(centralWidget);





     /*********** ZONE EDITION *****/


    QVBoxLayout* zoneedition = new QVBoxLayout;
    QPushButton * bouton = new QPushButton("Bonjour");
    petitwindow* petitefenetre = new petitwindow();
    zoneedition -> addWidget(petitefenetre);
    //zoneedition->addWidget(bouton);







    /********** DOCK WIDGET HAUT : Onglet **********/


  /**  QDockWidget* dockhaut = new QDockWidget("Onglet",this);
    dockhaut ->setAllowedAreas((Qt::TopDockWidgetArea));
    this->addDockWidget(Qt::TopDockWidgetArea, dockhaut);**/
     QTabWidget *tabs = new QTabWidget(centralWidget);
      tabs->setFixedHeight(70);

      fichier* ongletfichier = new fichier();
      ongletfichier->setObjectName("fichier");

      aspect* ongletaspect = new aspect();
      ongletaspect->setObjectName("aspect");

      QWidget* format = new QWidget();
      format->setObjectName("format");

   tabs->addTab( ongletfichier,"Fichier");
   tabs->addTab(ongletaspect,"Aspect");
   tabs->addTab(format,"Format");
   tabs->setTabsClosable(true);

    tabs->setTabsClosable(false);

   /** dockhaut->setWidget(tabs);

   QWidget * titleBarWidget = new QWidget(0);
   dockhaut->setTitleBarWidget(titleBarWidget);
   //dockgauche->setTitleBarWidget(titleBarWidget); **/




   /******** CENTRAL WIDGET = onglets + zoneEdition*******/

   QVBoxLayout* layoutV = new QVBoxLayout;
   layoutV->addWidget(tabs);
   layoutV->addLayout(zoneedition);

   centralWidget->setLayout(layoutV);




    /************Design***************/



    /********** DOCK WIDGET DE GAUCHE = Liste *************/

    QDockWidget * dockgauche = new QDockWidget("Vos Notes", this);
    dockgauche->setAllowedAreas(Qt::LeftDockWidgetArea);
    this->addDockWidget(Qt::LeftDockWidgetArea,dockgauche);
    dockgauche->setMinimumWidth(100);
    dockgauche->setMaximumWidth(200);

    QTreeWidget *treeWidget = new QTreeWidget(dockgauche);
       treeView = new QTreeView(treeWidget);
       treeView->setObjectName(tr("treeView"));
          treeView->setAlternatingRowColors(true);
          treeView->setSelectionBehavior(QAbstractItemView::SelectItems);
          treeView->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
          treeView->setMinimumWidth(200);
          treeView->setMaximumWidth(400);
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
       menufichier->addAction(insertRowAct);
       menufichier->addAction(removeRowAct);
       menufichier->addSeparator();
       menufichier->addAction(insertChildAct);
       menufichier->addSeparator();
       menufichier->addAction(exitAct);

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

       connect(menufichier, SIGNAL(aboutToShow()), this, SLOT(updateActions()));
       connect(insertRowAct, SIGNAL(triggered()), this, SLOT(insertRow()));
       connect(removeRowAct, SIGNAL(triggered()), this, SLOT(removeRow()));
       connect(insertChildAct, SIGNAL(triggered()), this, SLOT(insertChild()));

       connect(exitAct, SIGNAL(triggered()), qApp, SLOT(quit()));

       updateActions();




       this->setStyleSheet(

                  "QWidget {background-color : #5b8c5b}"



                   "QTabBar::tab { background-color :#bbe0bb;  padding-right : 25px; padding-left : 25px; padding-top : 6px; padding-bottom : 6px;margin-right : 10px; border-top-left-radius: 5px; border-top-right-radius: 5px;  } "
                 " QTabBar::tab:selected { border-bottom-color: #8fc58f; }"
                  "QTabBar::tab:!selected {margin-top: 2px; background : #8fc58f}"


                   "QWidget#fichier{background-color : #bbe0bb}"
                  "QWidget#format{background-color : #bbe0bb}"
                   "QWidget#aspect{background-color : #bbe0bb}"
                  "QTabWidget:pane { background : #bbe0bb; }"

                  "QTreeView {background : #bbe0bb ; alternate-background-color: #bbe0bb;  border: none;}"
                   "QHeaderView::section {background : #bbe0bb; border : none;}"
                   "QDockWidget::title {background :  #8fc58f; text-align : center; }"

                                                );


       // treeView->setHeaderHidden(true);

       QPalette qp = treeView->header()->palette();
       qp.setColor(QPalette::Background, QColor(0,0,255));
       treeView->header()->setPalette(qp);


        centralWidget->setContentsMargins(0,-10,0,-10);
       petitefenetre->setStyleSheet( " background-color : #d9f1d9 ; border : #8fc58f" );



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
