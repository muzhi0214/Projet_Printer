#include "mainwindow.h"
#include "petitwindow.h"
//#include "dialog.h"
#include "fichier.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
   // petitwindow w;

    w.show();

    return a.exec();
}
