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
#include <QColor>
#include "stdio.h"
#include "string.h"
#include "math.h"

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
   // QMenu* menuattribut = barmenu->addMenu("&Attribut");
    //QMenu* menuforme = barmenu->addMenu("&Forme");


     QWidget *centralWidget = new QWidget(this);
     setCentralWidget(centralWidget);





     /*********** ZONE EDITION *****/


    QVBoxLayout* zoneedition = new QVBoxLayout;
    //QPushButton * bouton = new QPushButton("Bonjour");
    petitefenetre = new petitwindow();
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
    dockgauche->setMinimumWidth(250);
    dockgauche->setMaximumWidth(400);
    dockgauche->setMinimumHeight(600);

    QTreeWidget *treeWidget = new QTreeWidget(dockgauche);
       treeView = new QTreeView(treeWidget);
       treeView->setObjectName(tr("treeView"));
          treeView->setAlternatingRowColors(true);
          treeView->setSelectionBehavior(QAbstractItemView::SelectItems);
          treeView->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
          treeView->setMinimumWidth(250);
          treeView->setMaximumWidth(400);
          treeView->setMinimumHeight(600);
          treeView->setAnimated(false);
          treeView->setAllColumnsShowFocus(true);

          dockgauche->setWidget(treeWidget);




    /********** Define Actions *****************/
       insertRowAct = new QAction(tr("&Insert Note"),this);
       insertRowAct->setObjectName(tr("insertRowAct"));
       removeRowAct = new QAction(tr("&Remove Note"),this);
       removeRowAct->setObjectName(tr("removeRowAct"));

       insertChildAct = new QAction(tr("&Insert Child-note"),this);
       insertChildAct->setObjectName(tr("insertChildAct"));

       exitAct = new QAction(tr("&Exit"),this);
       exitAct->setObjectName(tr("exitAct"));

       nouveauAct=new QAction(tr("&Nouveau"),this);
       nouveauAct->setObjectName(tr("Nouveau"));

       /*********** Add Actions **************/
       menufichier->addAction(nouveauAct);
       //menufichier->addAction(insertRowAct);
       //menufichier->addAction(insertChildAct);
       menufichier->addSeparator();

       menufichier->addAction(removeRowAct);
       menufichier->addSeparator();
       menufichier->addAction(exitAct);

       treeView->setContextMenuPolicy(Qt::ActionsContextMenu);
       treeView->addAction(nouveauAct);
       treeView->addAction(removeRowAct);



       /********** Setup TreeList *************/

       QStringList headers;
       headers << tr("            Name           ") << tr("  Date Modified ");

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

      // connect(actionsMenu, SIGNAL(aboutToShow()), this, SLOT(updateActions()));
       connect(insertRowAct, SIGNAL(triggered()), this, SLOT(insertRow()));
       connect(removeRowAct, SIGNAL(triggered()), this, SLOT(removeRow()));
       connect(insertChildAct, SIGNAL(triggered()), this, SLOT(insertChild()));
       connect(exitAct, SIGNAL(triggered()), qApp, SLOT(quit()));

       connect(nouveauAct,SIGNAL(triggered()),this,SLOT(nouveau()));

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
void MainWindow::nouveau()
{
    n_dialog=new NouveauDialog;
    MainWindow *w=new MainWindow;
    n_dialog->show();
    n_dialog->move((w->width()-n_dialog->width())/2,(w->height()-n_dialog->height())/2);

    connect(n_dialog->type, SIGNAL(buttonClicked(int)), this, SLOT(save_id(int)));
    connect(n_dialog->browseButton,SIGNAL(clicked()),this,SLOT(browse()));
    connect(n_dialog->finish,SIGNAL(clicked()),this,SLOT(insert()) );

    n_dialog->type->setExclusive(true);

}
void MainWindow::save_id(int id)
{
    real_id=id;
}

void MainWindow::insert()
{
  QString contenu = n_dialog->lineEdit->text();
  bool checked1 = n_dialog->noteRadioButton->isChecked();
  bool checked2 = n_dialog->childNoteRadioButton->isChecked();
  if ( contenu == NULL)
  {
    QMessageBox::warning(this, tr("Nouveau"),
     tr("Please input the name of note."));
     n_dialog->show();
     return;
  }
  else if (!checked1 && !checked2){
      QMessageBox::warning(this, tr("Nouveau"),
       tr("Please select the type of note."));
       n_dialog->show();
       return;
  }
  else
  {
    if (real_id==2)
    {
        this->insertChild();
        this->save();

    }
    if(real_id==1)

    {
        this->insertRow();        
        this->save();
    }
   }
}

void MainWindow::save(){
    QString fileName = n_dialog->lineEdit->text();
    QString initialPath = n_dialog->path;
    QString fileOut = initialPath + "/" +fileName + ".txt";

    QFile file(fileOut);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Insert"),
                             tr("Cannot insert %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return;
    }
    //QDataStream stream(&file);
    QTextStream out(&file);

    out << petitefenetre->text->toPlainText();
}

void MainWindow::insertChild()
{
    QModelIndex index = treeView->selectionModel()->currentIndex();
    QAbstractItemModel *model = treeView->model();

    if(!index.isValid()){
        QMessageBox::warning(this, tr("Insert"),
        tr("Sorry, you cannot insert a child note without a parent note."));
        return;
    }

    if (!model->insertRow(0, index)){
        QMessageBox::warning(this, tr("Insert"),
        tr("Sorry, you cannot insert more childs."));
        return;
    }

        QModelIndex child = model->index(0, 0, index);

        const QString & noteName = n_dialog->lineEdit->text();
        const QDateTime & currDT = QDateTime::currentDateTime();

        model->setData(child, QVariant(noteName), Qt::EditRole);

        QModelIndex childSibling = model->index(0,1,index);

        model->setData(childSibling, QVariant(currDT), Qt::EditRole);

        if (!model->headerData(0, Qt::Horizontal).isValid())
          model->setHeaderData(0, Qt::Horizontal, QVariant(currDT),
                                   Qt::EditRole);
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

    const QString & noteName = n_dialog->lineEdit->text();
    const QDateTime & currDT = QDateTime::currentDateTime();

    for (int column = 0; column < model->columnCount(index.parent()); ++column) {
        QModelIndex childSibling = model->index(index.row()+1,column,index.parent());
        model->setData(childSibling, QVariant(currDT), Qt::EditRole);
        QModelIndex child = model->index(index.row()+1, column-1, index.parent());
        model->setData(child, QVariant(noteName), Qt::EditRole);
    }
}

void MainWindow::removeRow()
{
    QModelIndex index = treeView->selectionModel()->currentIndex();
    QAbstractItemModel *model = treeView->model();

    if(index.parent().isValid()){
        if (model->removeRow(index.row(), index.parent()))
            updateActions();
        return;
    }

    QMessageBox::StandardButton ret;
    ret = QMessageBox::warning(this, tr("Remove"),
    tr("You will move all the notes including children notes! Are you sure to remove it?"),
                     QMessageBox::Yes | QMessageBox::No);
    if (ret == QMessageBox::Yes){

        if (model->removeRow(index.row(), index.parent()))
            updateActions();
        return;}
    else
        return;

}

void MainWindow::updateActions()
{
    //bool hasSelection = !treeView->selectionModel()->selection().isEmpty();
    //removeRowAction->setEnabled(hasSelection);


    bool hasCurrent = treeView->selectionModel()->currentIndex().isValid();
    //insertRowAction->setEnabled(hasCurrent);


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


void MainWindow::browse()
{
    QString directory = QFileDialog::getExistingDirectory(this,
                               tr("Dir"), QDir::currentPath());

    if (!directory.isEmpty()) {
        if (n_dialog->directoryComboBox->findText(directory) == -1)
            n_dialog->directoryComboBox->addItem(directory);
        n_dialog->directoryComboBox->setCurrentIndex(n_dialog->directoryComboBox->findText(directory));
         n_dialog->path = directory;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


