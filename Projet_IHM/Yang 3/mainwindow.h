#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include "petitwindow.h"
#include <QMainWindow>
#include <QModelIndex>
#include <QTreeView>
#include "nouveaudialog.h"
#include <QVariant>
#include <QMessageBox>
#include <QTextStream>
#include <QDateTime>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
   Q_OBJECT

public:
   explicit MainWindow(QWidget *parent = 0);
   ~MainWindow();

private:
   Ui::MainWindow *ui;
   QTabWidget* onglets;
   QTreeView* treeView;

   QAction *insertChildAct;
   QAction *insertRowAct;
   QAction *removeRowAct;

   QAction *exitAct;

   QAction *nouveauAct;
   int real_id;
  // QString nom;
   //NouveauDialog *n_dialog;

    NouveauDialog *n_dialog;
    petitwindow* petitefenetre ;
public slots:
   void updateActions();
   void nouveau();

private slots:
   void insertChild();
   void insertRow();
   void removeRow();
   void insert();
   void save_id(int id);
   void browse();

   void save();

};

#endif // MAINWINDOW_H
