#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include <QMainWindow>
#include <QModelIndex>
#include <QTreeView>

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

   QAction *insertRowAct;
   QAction *removeRowAct;
   QAction *insertChildAct;

   QAction *exitAct;

public slots:
   void updateActions();

private slots:
   void insertChild();
   void insertRow();
   void removeRow();
};

#endif // MAINWINDOW_H
